type route =
  | Home
  | Clients
  | Client(int);

module Home = {
  let url = () => "/";
};

module Clients = {
  let url = () => "/clients";
};

module Client = {
  let url = (id) => {j|/clients/$id|j};
};

let getRouteConfig = (renderForRoute) => {
  let routeConfig = Js.Dict.empty();
  Js.Dict.set(routeConfig, Home.url(), (_) => renderForRoute(Home));
  Js.Dict.set(routeConfig, Clients.url(), (_) => renderForRoute(Clients));
  Js.Dict.set(routeConfig, Client.url(":id"), (id) => renderForRoute(Client(int_of_string(id))));
  /* return dictionary as Js object */
  Obj.magic(routeConfig)
};

let init = (renderForRoute) => {
  let routeConfig = getRouteConfig(renderForRoute);
  let router = DirectorRe.makeRouter(routeConfig);
  DirectorRe.init(router, Home.url())
};