type t = {
  id: option(int),
  name: string
};

module Decode = {
  let client = (json) =>
    Json.Decode.{id: json |> optional(field("id", int)), name: json |> field("name", string)};
  let client_array = (json) => json |> Json.Decode.array(client);
};

module Encode = {
  let client = (clientObj) =>
    Json.Encode.(
      object_([
        (
          "id",
          switch clientObj.id {
          | Some(id) => int(id)
          | None => null
          }
        ),
        ("name", string(clientObj.name))
      ])
    );
};

module Api = {
  let baseUrl = Constants.apiUrl;
  let clientsUrl = {j|$baseUrl/clients|j};
  let clientUrl = (id) => {j|$baseUrl/clients/$id|j};
  let fetch = (id: int) =>
    Js.Promise.(
      Fetch.fetch(clientUrl(id))
      |> then_(Fetch.Response.json)
      |> then_((json) => json |> Decode.client |> resolve)
    );
  let fetchAll = () =>
    Js.Promise.(
      Fetch.fetch(clientsUrl)
      |> then_(Fetch.Response.json)
      |> then_((json) => json |> Decode.client_array |> resolve)
    );
  let add = (client) => {
    let body = Fetch.BodyInit.make(client |> Encode.client |> Js.Json.stringify);
    let headers = Common.Request.getDefaultHeaders();
    let request = Fetch.RequestInit.make(~method_=Post, ~body, ~headers, ());
    Js.Promise.(
      Fetch.fetchWithInit(clientsUrl, request)
      |> then_(Fetch.Response.json)
      |> then_((json) => json |> Decode.client |> resolve)
    )
  };
  let edit = (client) => {
    let body = Fetch.BodyInit.make(client |> Encode.client |> Js.Json.stringify);
    let headers = Common.Request.getDefaultHeaders();
    let request = Fetch.RequestInit.make(~method_=Put, ~body, ~headers, ());
    Js.Promise.(
      Fetch.fetchWithInit(clientUrl(client.id), request) |> then_(Common.Response.statusOk)
    )
  };
  let remove = (id) =>
    Js.Promise.(
      Fetch.fetchWithInit(clientUrl(id), Fetch.RequestInit.make(~method_=Delete, ()))
      |> then_(Common.Response.statusOk)
    );
};

/* Reducer helper methods */
let append = (clients, client: t) =>
  Some(Array.concat([Utils.optToArrayOrEmpty(clients), [|client|]]));

let replace = (clients, client: t) =>
  Some(
    Array.map(
      (c) => c.id === client.id ? {...client, id: c.id} : c,
      Utils.optToArrayOrEmpty(clients)
    )
  );

let removeWithId = (clients, id) => {
  let clientList = Array.to_list(Utils.optToArrayOrEmpty(clients));
  let filteredList = List.filter((client) => Utils.optIntOrRaise(client.id) !== id, clientList);
  Some(Array.of_list(filteredList))
};