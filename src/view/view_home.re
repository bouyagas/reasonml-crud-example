open Utils;

let component = ReasonReact.statelessComponent("Home");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div>
      <h1 className="margin-bottom-xl"> (textEl("Home")) </h1>
      <p> (textEl("This is REASONML CRUD example.")) </p>
      <p>
        (
          textEl(
            "Purpose of this project was to study REASONML and find a lean way how to implement common CRUD functionality using simple Client-entity."
          )
        )
      </p>
    </div>
};