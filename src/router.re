let init = (pageChanged) => {
  let watchId =
    ReasonReact.Router.watchUrl(
      (url) => {
        let route = Routes.getRoute(url.path);
        let page =
          switch route {
          | Home => <View_home />
          | Clients => <View_clients />
          | Client(id) => <View_client id />
          | NotFound => <div> (Utils.textEl("Page not found!")) </div>
          };
        pageChanged(page)
      }
    );
  watchId
};

let destroy = ReasonReact.Router.unwatchUrl;