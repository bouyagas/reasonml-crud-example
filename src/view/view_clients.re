open Model;

open Utils;

requireCSS("./view_clients.css");

/**
 * This is ClientDialog module which is used to add and edit clients
 */
module ClientDialog = {
  type state = {
    client: Client.t,
    hasError: bool
  };
  type action =
    | Changed(string)
    | SetError(bool);
  let component = ReasonReact.reducerComponent("ClientDialog");
  let make = (~onSubmit, ~onClose, ~data: option(Client.t)=None, _) => {
    ...component,
    initialState: () =>
      switch data {
      | Some(client) => {client, hasError: false}
      | None => {client: {id: None, name: ""}, hasError: false}
      },
    render: (self) => {
      let internalSubmit = (evt: ReactEventRe.Mouse.t) => {
        let trimmed: string = String.trim(self.state.client.name);
        if (String.length(trimmed) > 0) {
          onSubmit(self.state.client);
          onClose(evt)
        } else {
          self.send(SetError(true))
        }
      };
      let intent = self.state.hasError ? Blueprintjs.Intent.DANGER : Blueprintjs.Intent.NONE;
      <div className="dialog-container">
        <Blueprintjs.FormGroup
          label=(textEl("Name "))
          labelFor="client-name-input"
          requiredLabel=(`Bool(true))
          intent
          inline=true
          helperText=(
            self.state.hasError ? textEl("Enter valid client name") : ReasonReact.nullElement
          )
          required=true>
          <Blueprintjs.InputGroup
            _type="text"
            id="client-name-input"
            intent
            value=self.state.client.name
            placeholder="Enter client name..."
            onChange=((event) => self.send(Changed(getValueFromEvent(event))))
          />
        </Blueprintjs.FormGroup>
        <div className="dialog-button-container">
          <Blueprintjs.Button onClick=onClose> (textEl("Cancel")) </Blueprintjs.Button>
          <Blueprintjs.Button onClick=internalSubmit intent=Blueprintjs.Intent.PRIMARY>
            (
              switch data {
              | Some(_c) => textEl("Edit")
              | None => textEl("Add")
              }
            )
          </Blueprintjs.Button>
        </div>
      </div>
    },
    reducer: (action, state) =>
      switch action {
      | Changed(name) =>
        let hasError = state.hasError && String.length(String.trim(name)) === 0;
        ReasonReact.Update({hasError, client: {...state.client, name}})
      | SetError(hasError) => ReasonReact.Update({...state, hasError})
      }
  };
};

/**
 * Here is the View_clients module implementation itself
 */
type state = {
  clients: option(array(Client.t)),
  addDialogOpen: bool,
  editClient: option(Client.t),
  hasLoadError: bool
};

type action =
  | Loaded(array(Client.t))
  | LoadError
  | AddClient(Client.t)
  | EditClient(Client.t)
  | RemoveClient(int)
  | ToggleAddDialog
  | ToggleEditDialog(option(Client.t));

let component = ReasonReact.reducerComponent("Clients");

let make = (_children) => {
  /**
   * "Private" functions are introduced first
   */
  let renderClient = (client: Client.t, removeClient, openEditDialog) =>
    <tr className="client-table-row" key=(optIntToString(client.id))>
      <td> <a href=("#" ++ Routing.Client.url(client.id))> (optIntEl(client.id)) </a> </td>
      <td> (textEl(client.name)) </td>
      <td>
        <div className="client-icon-container">
          <span
            title="Edit"
            onClick=((_e) => openEditDialog(Some(client)))
            className="pt-icon-standard pt-icon-edit"
          />
          <span
            title="Remove"
            onClick=((_e) => removeClient(client))
            className="pt-icon-standard pt-icon-trash margin-left-md"
          />
        </div>
      </td>
    </tr>;
  let renderClients = (clients: array(Client.t), removeClient, openEditDialog) =>
    <table className="pt-table pt-striped client-table">
      <thead>
        <tr>
          <th> (textEl("Id")) </th>
          <th> (textEl("Name")) </th>
          <th> <div className="client-remove-icon-header" /> </th>
        </tr>
      </thead>
      <tbody>
        (
          arrayEl(
            Array.map((client) => renderClient(client, removeClient, openEditDialog), clients)
          )
        )
      </tbody>
    </table>;
  let renderLoading = () =>
    <div className="align-middle">
      <Blueprintjs.Spinner className="pt-small" />
      <span className="margin-left-md"> (textEl("Loading")) </span>
    </div>;
  let handleAdd = (client, handleClientAdded) => {
    Js.Promise.(
      Client.Api.add(client)
      |> then_(
           (addedClient) => {
             handleClientAdded(addedClient);
             resolve()
           }
         )
      |> catch(
           (_err) => {
             Notify.showError("Failed to add client! Check network connection!") |> ignore;
             resolve()
           }
         )
      |> ignore
    );
    ReasonReact.NoUpdate
  };
  let handleEdit = (client, handleClientEdited) =>
    Js.Promise.(
      Client.Api.edit(client)
      |> then_(
           () => {
             handleClientEdited(client);
             resolve()
           }
         )
      |> catch(
           (_err) => {
             Notify.showError("Failed to edit client! Check network connection!") |> ignore;
             resolve()
           }
         )
      |> ignore
    );
  let handleRemove = (client: Client.t, handleClientRemoved) => {
    let doRemove = (clientId) =>
      Js.Promise.(
        Client.Api.remove(clientId)
        |> then_(
             () => {
               handleClientRemoved(clientId);
               resolve()
             }
           )
        |> catch(
             (_err) => {
               Notify.showError("Failed to delete client! Check network connection!") |> ignore;
               resolve()
             }
           )
        |> ignore
      );
    switch client.id {
    | Some(clientId) => doRemove(clientId)
    | None => Notify.showError("Internal error! Attempting to remove client without id!") |> ignore
    }
  };
  let fetchAll = (handleClientsLoaded, handleError) => {
    Js.Promise.(
      Client.Api.fetchAll()
      |> then_(
           (clients) => {
             handleClientsLoaded(clients);
             resolve()
           }
         )
      |> catch(
           (_err) => {
             Notify.showError("Failed to fetch clients! Check network connection!") |> ignore;
             handleError();
             resolve()
           }
         )
      |> ignore
    );
    ReasonReact.NoUpdate
  };
  /**
   * Implementation for the View_clients React component
   */
  {
    ...component,
    initialState: () => {
      clients: None,
      addDialogOpen: false,
      editClient: None,
      hasLoadError: false
    },
    render: (self) => {
      let toggleAddDialog = (_event) => self.send(ToggleAddDialog);
      let openEditDialog = (client) => self.send(ToggleEditDialog(client));
      let closeEditDialog = (_event) => self.send(ToggleEditDialog(None));
      let removeClient = (client) =>
        handleRemove(client, (removedId) => self.send(RemoveClient(removedId)));
      let addClient = (client) => handleAdd(client, (client) => self.send(AddClient(client)));
      let editClient = (client) => handleEdit(client, (client) => self.send(EditClient(client)));
      let clientsContent =
        switch self.state.clients {
        | Some(clients) => renderClients(clients, removeClient, openEditDialog)
        | None => renderLoading()
        };
      self.state.hasLoadError ?
        <h2 className="pt-running-text">
          (textEl("Error loading clients! Check network connection and reload!"))
        </h2> :
        <div>
          <h1 className="pt-running-text"> (textEl("Clients")) </h1>
          (
            self.state.clients != None ?
              <div>
                <Blueprintjs.Button onClick=toggleAddDialog>
                  (textEl("Add client"))
                </Blueprintjs.Button>
              </div> :
              ReasonReact.nullElement
          )
          <div> clientsContent </div>
          <Blueprintjs.Dialog
            isOpen=self.state.addDialogOpen
            onClose=toggleAddDialog
            title=(textEl("Add new client"))>
            <ClientDialog onSubmit=addClient onClose=toggleAddDialog />
          </Blueprintjs.Dialog>
          <Blueprintjs.Dialog
            isOpen=(self.state.editClient !== None)
            onClose=closeEditDialog
            title=(textEl("Edit client"))>
            <ClientDialog onSubmit=editClient onClose=closeEditDialog data=self.state.editClient />
          </Blueprintjs.Dialog>
        </div>
    },
    didMount: (self) =>
      fetchAll((clients) => self.send(Loaded(clients)), () => self.send(LoadError)),
    /* This is the add dialog */
    reducer: (action, state) =>
      switch action {
      | Loaded(clients) =>
        ReasonReact.Update({...state, hasLoadError: false, clients: Some(clients)})
      | LoadError => ReasonReact.Update({...state, hasLoadError: true})
      | ToggleAddDialog => ReasonReact.Update({...state, addDialogOpen: ! state.addDialogOpen})
      | ToggleEditDialog(editClient) => ReasonReact.Update({...state, editClient})
      | AddClient(client) =>
        ReasonReact.Update({...state, clients: Client.append(state.clients, client)})
      | EditClient(client) =>
        ReasonReact.Update({...state, clients: Client.replace(state.clients, client)})
      | RemoveClient(removedId) =>
        ReasonReact.Update({...state, clients: Client.removeWithId(state.clients, removedId)})
      }
    /* This is the edit dialog */
  }
};