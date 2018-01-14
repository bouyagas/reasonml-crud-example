open Utils;
open View;

requireCSS("./app.css");

let logo = requireAssetURI("./logo.svg");

let component = ReasonReact.statelessComponent("app");

let make = (~route, _children) => {
  ...component,
  render: (_self) => {
    let page =
      switch route {
      | Routing.Home => <Home />
      | Routing.Clients => <Clients />
      | Routing.Client(id) => <Client id />
      };
    
    <div className="app">
      <Blueprintjs.Navbar className="pt-dark">

        <Blueprintjs.NavbarGroup align=Blueprintjs.NavbarAlign.Left >
          <a href=("#" ++ Routing.Home.url())> <img src=logo className="app-logo" alt="logo" /> </a>
          <a className="pt-navbar-heading pt-button pt-minimal" href=("#" ++ Routing.Home.url())>(textEl("REASONML CRUD EXAMPLE"))</a>
        </Blueprintjs.NavbarGroup>

        <Blueprintjs.NavbarGroup align=Blueprintjs.NavbarAlign.Right >
          <a href=("#" ++ Routing.Clients.url()) className="pt-button pt-minimal pt-icon-people">(textEl("Clients"))</a>
          <Blueprintjs.NavbarDivider />
          <Blueprintjs.Button className="pt-minimal" iconName="cog"></Blueprintjs.Button>
        </Blueprintjs.NavbarGroup>
      </Blueprintjs.Navbar>
      <div className="app-content">
        page
      </div>
    </div>
  }
};