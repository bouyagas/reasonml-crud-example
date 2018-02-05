open Utils;

requireCSS("./app.css");

let logo = requireAssetURI("./logo.svg");

type state = {mainContent: ReasonReact.reactElement};

type action =
  | MainContentChanged(ReasonReact.reactElement);

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => {mainContent: Router.getInitialPage()},
  render: (self) =>
    <div className="app">
      <Blueprintjs.Navbar className="pt-dark">
        <Blueprintjs.NavbarGroup align=Blueprintjs.NavbarAlign.Left>
          <Link route=Routes.Home className="test">
            <img src=logo className="app-logo" alt="logo" />
          </Link>
          <Link route=Routes.Home className="pt-navbar-heading pt-button pt-minimal">
            (textEl("REASONML CRUD EXAMPLE"))
          </Link>
        </Blueprintjs.NavbarGroup>
        <Blueprintjs.NavbarGroup align=Blueprintjs.NavbarAlign.Right>
          <Link route=Routes.Clients className="pt-button pt-minimal pt-icon-people">
            (textEl("Clients"))
          </Link>
          <Blueprintjs.NavbarDivider />
          <Blueprintjs.Button className="pt-minimal" iconName="cog" />
        </Blueprintjs.NavbarGroup>
      </Blueprintjs.Navbar>
      <div className="app-content"> self.state.mainContent </div>
    </div>,
  reducer: (action, _state) =>
    switch action {
    | MainContentChanged(el) => ReasonReact.Update({mainContent: el})
    },
  subscriptions: (self) => [
    Sub(() => Router.init((el) => self.send(MainContentChanged(el))), Router.destroy)
  ]
};