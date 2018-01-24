open Utils;

open Model;

type state = {client: option(Client.t)};

type action =
  | Loaded(Client.t);

let component = ReasonReact.reducerComponent("Client");

let make = (~id, _children) => {
  let renderClient = (client: Client.t) =>
    <div className="margin-left-md">
      <p> <strong> (textEl("ID: ")) </strong> (optIntEl(client.id)) </p>
      <p> <strong> (textEl("Name: ")) </strong> (textEl(client.name)) </p>
    </div>;
  {
    ...component,
    initialState: () => {client: None},
    render: (self) => {
      let clientContent =
        switch self.state.client {
        | Some(client) => renderClient(client)
        | None => ReasonReact.stringToElement("Loading client")
        };
      <div>
        <div className="margin-bottom-lg">
          <a href=("#" ++ Routing.Clients.url())> (textEl("< Back")) </a>
        </div>
        <h1 className="pt-running-text"> (textEl("Client")) </h1>
        <div> clientContent </div>
      </div>
    },
    didMount: (self) => {
      let handleClientLoaded = (client) => self.send(Loaded(client));
      Js.Promise.(
        Client.Api.fetch(id)
        |> then_(
             (client) => {
               handleClientLoaded(client);
               resolve()
             }
           )
        |> catch(
             (_err) => {
               Notify.showError("Failed to fetch clients! Check network connection!") |> ignore;
               resolve()
             }
           )
        |> ignore
      );
      ReasonReact.NoUpdate
    },
    reducer: (action, _state) =>
      switch action {
      | Loaded(client) => ReasonReact.Update({client: Some(client)})
      }
  }
};