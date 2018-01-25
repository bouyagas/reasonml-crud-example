exception CannotCreateLinkToNotFound;

let component = ReasonReact.statelessComponent("Link");

let make = (~route: Routes.t, ~className=?, children) => {
  let isModifiedEvent = (event: ReactEventRe.Mouse.t) =>
    ReactEventRe.Mouse.metaKey(event)
    || ReactEventRe.Mouse.altKey(event)
    || ReactEventRe.Mouse.ctrlKey(event)
    || ReactEventRe.Mouse.shiftKey(event);
  let isLinkEvent = (event: ReactEventRe.Mouse.t) =>
    ReactEventRe.Mouse.button(event) == 0 /* ignore everything but left clicks */
    && ! isModifiedEvent(event); /* ignore clicks with modifier keys */
  {
    ...component,
    render: (_self) => {
      let url =
        switch route {
        | Home => Routes.Home.url()
        | Clients => Routes.Clients.url()
        | Client(id) => Routes.Client.url(id)
        | NotFound => raise(CannotCreateLinkToNotFound)
        };
      let handleClick = (event: ReactEventRe.Mouse.t) =>
        if (isLinkEvent(event)) {
          ReactEventRe.Mouse.preventDefault(event);
          ReasonReact.Router.push(url)
        };
      ReasonReact.createDomElement(
        "a",
        ~props={
          "className": Utils.optStringOrEmpty(className),
          "onClick": handleClick,
          "href": url
        },
        children
      )
    }
  }
};