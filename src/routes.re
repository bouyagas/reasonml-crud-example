type t =
  | Home
  | Clients
  | Client(int)
  | NotFound;

module Home = {
  let url = () => "/";
};

module Clients = {
  let url = () => "/clients";
};

module Client = {
  let url = (id) => {j|/clients/$id|j};
};

let getRoute = (path) =>
  /* TODO - make "pattern matching" so that you don't have to define urls twice in this file */
  switch path {
  | ["clients", id] => Client(int_of_string(id))
  | ["clients"] => Clients
  | [] => Home
  | _ => NotFound
  };