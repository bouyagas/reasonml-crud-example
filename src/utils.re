/* require css file for side effect only */
[@bs.val] external requireCSS : string => unit = "require";

/* require an asset (eg. an image) and return exported string value (image URI) */
[@bs.val] external requireAssetURI : string => string = "require";

[@bs.val] external currentTime : unit => int = "Date.now";

[@bs.module "./registerServiceWorker"] external registerServiceWorker : unit => unit = "default";

let intEl = (n) => n |> string_of_int |> ReasonReact.stringToElement;

let optIntEl = (n) =>
  switch n {
  | Some(n) => intEl(n)
  | None => ReasonReact.nullElement
  };

let textEl = ReasonReact.stringToElement;

let arrayEl = ReasonReact.arrayToElement;

let boolEl = (n: bool) => n ? textEl("true") : textEl("false");

let optIntToString = (n) =>
  switch n {
  | Some(n) => string_of_int(n)
  | None => "<null>"
  };

exception ShouldHaveValidIntValue;

let optIntOrRaise = (n) : int =>
  switch n {
  | Some(value) => value
  | None => raise(ShouldHaveValidIntValue)
  };

/* gets value from from element event. EG:
   <input onChange=(reduce((event) => Changed(getValueFromEvent(event))))/> */
let getValueFromEvent = (event) : string => ReactDOMRe.domElementToObj(
                                              ReactEventRe.Form.target(event)
                                            )##value;

let optToArrayOrEmpty = (x) =>
  switch x {
  | Some(items) => items
  | None => Array.of_list([])
  };