type jsUnsafe;

external toJsUnsafe : 'a => jsUnsafe = "%identity";

let unwrapValue =
  fun
  | `String(s) => toJsUnsafe(s)
  | `Bool(b) => toJsUnsafe(Js.Boolean.to_js_boolean(b))
  | `Float(f) => toJsUnsafe(f)
  | `Date(d) => toJsUnsafe(d)
  | `Callback(c) => toJsUnsafe(c)
  | `Element(e) => toJsUnsafe(e)
  | `Object(o) => toJsUnsafe(o)
  | `Enum(_) => assert false;

module Intent = {
  type t =
    | NONE
    | PRIMARY
    | SUCCESS
    | WARNING
    | DANGER;
  let toInt = (x) =>
    switch x {
    | NONE => (-1)
    | PRIMARY => 0
    | SUCCESS => 1
    | WARNING => 2
    | DANGER => 3
    };
  let fromOpt = (o) =>
    switch o {
    | Some(intent) => Js.Undefined.return(toInt(intent))
    | None => Js.Undefined.empty
    };
};

let optionMap = (fn, option) =>
  switch option {
  | Some(value) => Some(fn(value))
  | None => None
  };

module NavbarAlign = {
  type t =
    | Left
    | Right;
  let toString =
    fun
    | Left => "left"
    | Right => "right";
};

module ButtonType = {
  type t =
    | Button
    | Submit;
  let toString =
    fun
    | Button => "button"
    | Submit => "submit";
};

module Navbar = {
  [@bs.module "@blueprintjs/core"] external reactClass : ReasonReact.reactClass = "Navbar";
  let make = (~className: option(string)=?, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props={"className": Js.Nullable.from_opt(className)},
      children
    );
};

module NavbarGroup = {
  [@bs.module "@blueprintjs/core"] external reactClass : ReasonReact.reactClass = "NavbarGroup";
  let make = (~className: option(string)=?, ~align: option(NavbarAlign.t)=?, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props={
        "className": Js.Nullable.from_opt(className),
        "align": Js.Nullable.from_opt(optionMap(NavbarAlign.toString, align))
      },
      children
    );
};

module NavbarHeading = {
  [@bs.module "@blueprintjs/core"] external reactClass : ReasonReact.reactClass = "NavbarHeading";
  let make = (~className: option(string)=?, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props={"className": Js.Nullable.from_opt(className)},
      children
    );
};

module Button = {
  [@bs.module "@blueprintjs/core"] external reactClass : ReasonReact.reactClass = "Button";
  let make =
      (
        ~active: option(bool)=?,
        ~className: option(string)=?,
        ~disabled: option(bool)=?,
        ~elementRef: option(Dom.element)=?,
        ~iconName: option(string)=?,
        ~intent: option(Intent.t)=?,
        ~loading: option(bool)=?,
        ~onClick: option(ReasonReact.Callback.t(ReactEventRe.Mouse.t))=?,
        ~rightIconName: option(string)=?,
        ~text: option(string)=?,
        ~buttonType: option(ButtonType.t)=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props={
        "active": Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, active)),
        "className": Js.Nullable.from_opt(className),
        "disabled": Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, disabled)),
        "elementRef": Js.Nullable.from_opt(elementRef),
        "iconName": Js.Nullable.from_opt(iconName),
        "intent": Js.Nullable.from_opt(optionMap(Intent.toInt, intent)),
        "loading": Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, loading)),
        "onClick": Js.Nullable.from_opt(onClick),
        "rightIconName": Js.Nullable.from_opt(rightIconName),
        "text": Js.Nullable.from_opt(text),
        "type": Js.Nullable.from_opt(optionMap(ButtonType.toString, buttonType))
      },
      children
    );
};

module NavbarDivider = {
  [@bs.module "@blueprintjs/core"] external reactClass : ReasonReact.reactClass = "NavbarDivider";
  let make = (~className: option(string)=?, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props={"className": Js.Nullable.from_opt(className)},
      children
    );
};

module Tabs = {
  [@bs.module "@blueprintjs/core"] external reactClass : ReasonReact.reactClass = "Tabs2";
  type onChangeEvent = {
    newTab: string,
    oldTab: string,
    event: ReactEventRe.Mouse.t
  };
  let make =
      (
        ~animate: option(bool)=?,
        ~className: option(string)=?,
        ~id: string,
        ~onChange: option(((string, string, ReactEventRe.Mouse.t) => unit))=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props={
        "animate": Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, animate)),
        "className": Js.Nullable.from_opt(className),
        "id": id,
        "onChange": Js.Nullable.from_opt(onChange)
      },
      children
    );
};

module Tab = {
  [@bs.module "@blueprintjs/core"] external reactClass : ReasonReact.reactClass = "Tab2";
  let make =
      (
        ~className: option(string)=?,
        ~id: string,
        ~title: option(string)=?,
        ~panel: option(ReasonReact.reactElement)=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props={
        "className": Js.Nullable.from_opt(className),
        "id": id,
        "title": Js.Nullable.from_opt(title),
        "panel": Js.Nullable.from_opt(panel)
      },
      children
    );
};

module Dialog = {
  [@bs.module "@blueprintjs/core"] external reactClass : ReasonReact.reactClass = "Dialog";
  let make =
      (
        ~isOpen: bool,
        ~autoFocus: option(bool)=?,
        ~backdropClassName: option(string)=?,
        ~backdropProps: option(Js.t({..}))=?,
        ~canEscapeKeyClose: option(bool)=?,
        ~canOutsideClickClose: option(bool)=?,
        ~className: option(string)=?,
        ~enforceFocus: option(bool)=?,
        ~hasBackdrop: option(bool)=?,
        ~iconName: option(string)=?,
        ~inline: option(bool)=?,
        ~isCloseButtonShown: option(bool)=?,
        ~_lazy: option(bool)=?,
        ~onClose: option(ReasonReact.Callback.t('t))=?,
        ~style: option(ReactDOMRe.style)=?,
        ~title: option(ReasonReact.reactElement)=?, /* TODO: can be also string */
        ~transitionDuration: option(int)=?,
        ~transitionName: option(string)=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props={
        "isOpen": Js.Boolean.to_js_boolean(isOpen),
        "autoFocus": Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, autoFocus)),
        "backdropClassName": Js.Nullable.from_opt(backdropClassName),
        "backdropProps": Js.Nullable.from_opt(backdropProps),
        "canEscapeKeyClose":
          Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, canEscapeKeyClose)),
        "canOutsideClickClose":
          Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, canOutsideClickClose)),
        "className": Js.Nullable.from_opt(className),
        "enforceFocus": Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, enforceFocus)),
        "hasBackdrop": Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, hasBackdrop)),
        "iconName": Js.Nullable.from_opt(iconName),
        "inline": Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, inline)),
        "isCloseButtonShown":
          Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, isCloseButtonShown)),
        "lazy": Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, _lazy)),
        "onClose": Js.Nullable.from_opt(onClose),
        "style": Js.Nullable.from_opt(style),
        "title": Js.Nullable.from_opt(title),
        "transitionDuration": Js.Nullable.from_opt(transitionDuration),
        "transitionName": Js.Nullable.from_opt(transitionName)
      },
      children
    );
};

module Label = {
  [@bs.module "@blueprintjs/core"] external reactClass : ReasonReact.reactClass = "Label";
  let make =
      (
        ~text: string,
        ~className: option(string)=?,
        ~disabled: option(bool)=?,
        ~helperText: option(ReasonReact.reactElement)=?,
        ~required: option(bool)=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props={
        "text": text,
        "className": Js.Nullable.from_opt(className),
        "disabled": Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, disabled)),
        "required": Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, required)),
        "helperText": Js.Nullable.from_opt(helperText)
      },
      children
    );
};

module FormGroup = {
  [@bs.module "@blueprintjs/core"] external reactClass : ReasonReact.reactClass = "FormGroup";
  let make =
      (
        ~className: option(string)=?,
        ~disabled: option(bool)=?,
        ~helperText: option(ReasonReact.reactElement)=?,
        ~inline: option(bool)=?,
        ~intent: option(Intent.t)=?,
        ~label: option(ReasonReact.reactElement)=?,
        ~labelFor: option(string)=?,
        ~requiredLabel: option([ | `Bool(bool) | `Element(ReasonReact.reactElement)])=?,
        ~required: option(bool)=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props={
        "className": Js.Nullable.from_opt(className),
        "disabled": Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, disabled)),
        "helperText": Js.Nullable.from_opt(helperText),
        "inline": Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, inline)),
        "intent": Js.Nullable.from_opt(optionMap(Intent.toInt, intent)),
        "label": Js.Nullable.from_opt(label),
        "labelFor": Js.Nullable.from_opt(labelFor),
        "requiredLabel": Js.Nullable.from_opt(optionMap(unwrapValue, requiredLabel)),
        "required": Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, required))
      },
      children
    );
};

module InputGroup = {
  [@bs.module "@blueprintjs/core"] external reactClass : ReasonReact.reactClass = "InputGroup";
  let make =
      (
        ~id: option(string)=?,
        ~className: option(string)=?,
        ~defaultValue: option(string)=?,
        ~disabled: option(bool)=?,
        ~inputRef: option(ReasonReact.reactElement)=?,
        ~intent: option(Intent.t)=?,
        ~leftIconName: option(string)=?,
        ~onChange: option(ReasonReact.Callback.t('t))=?,
        ~placeholder: option(string)=?,
        ~rightElement: option(ReasonReact.reactElement)=?,
        ~_type: option(string)=?,
        ~value: option(string)=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props={
        "id": Js.Nullable.from_opt(id),
        "className": Js.Nullable.from_opt(className),
        "defaultValue": Js.Nullable.from_opt(defaultValue),
        "disabled": Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, disabled)),
        "inputRef": Js.Nullable.from_opt(inputRef),
        "intent": Js.Nullable.from_opt(optionMap(Intent.toInt, intent)),
        "leftIconName": Js.Nullable.from_opt(leftIconName),
        "onChange": Js.Nullable.from_opt(onChange),
        "placeholder": Js.Nullable.from_opt(placeholder),
        "rightElement": Js.Nullable.from_opt(rightElement),
        "type": Js.Nullable.from_opt(_type),
        "value": Js.Nullable.from_opt(value)
      },
      children
    );
};
module Spinner = {
  [@bs.module "@blueprintjs/core"] external reactClass : ReasonReact.reactClass = "Spinner";
  let make =
      (
        ~className: option(string)=?,
        ~intent: option(Intent.t)=?,
        ~value: option(int)=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props={
        "className": Js.Nullable.from_opt(className),
        "intent": Js.Nullable.from_opt(optionMap(Intent.toInt, intent)),
        "value": Js.Nullable.from_opt(value)
      },
      children
    );
};

module Position = {
  type t =
    | TOP_LEFT
    | TOP
    | TOP_RIGHT
    | RIGHT_TOP
    | RIGHT
    | RIGHT_BOTTOM
    | BOTTOM_RIGHT
    | BOTTOM
    | BOTTOM_LEFT
    | LEFT_BOTTOM
    | LEFT
    | LEFT_TOP;
  let toInt = (x) =>
    switch x {
    | TOP_LEFT => 0
    | TOP => 1
    | TOP_RIGHT => 2
    | RIGHT_TOP => 3
    | RIGHT => 4
    | RIGHT_BOTTOM => 5
    | BOTTOM_RIGHT => 6
    | BOTTOM => 7
    | BOTTOM_LEFT => 8
    | LEFT_BOTTOM => 9
    | LEFT => 10
    | LEFT_TOP => 11
    };
  let fromOpt = (o) =>
    switch o {
    | Some(position) => Js.Undefined.return(toInt(position))
    | None => Js.Undefined.empty
    };
  [@bs.module "@blueprintjs/core"] external isPositionHorizontal : t => Js.boolean =
    "isPositionHorizontal";
  [@bs.module "@blueprintjs/core"] external isPositionVertical : t => Js.boolean =
    "isPositionVertical";
};

module ActionProps = {
  type t = {
    .
    /** Visual intent color to apply to element. */
    "intent": option(Intent.t),
    
    /** Whether this action is non-interactive. */
    "disabled": option(bool),

    /** Name of the icon (the part after `pt-icon-`) to add to the button. */
    "iconName": option(string),  /* TODO - define IconName type */

    /** Click event handler. */
    "onClick": option(ReasonReact.Callback.t(ReactEventRe.Mouse.t)),
    
    /** Action text. */
    "text": option(string),

    /** Link URL. */
    "href": option(string),

    /** Link target attribute. Use `"_blank"` to open in a new window. */
    "target": option(string)
  };
};

module ToastProps = {
  type t = {
    .
    /**
     * Action rendered as a minimal `AnchorButton`. The toast is dismissed automatically when the
     * user clicks the action button. Note that the `intent` prop is ignored (the action button
     * cannot have its own intent color that might conflict with the toast's intent). Omit this
     * prop to omit the action button.
     */
    "action": Js.Nullable.t(ActionProps.t),

    /** Name of the icon (the part after `pt-icon-`) to appear before the message. */
    "iconName": Js.Nullable.t(string), /* TODO - define IconName type */

    /** Visual intent color to apply to element. */
    "intent": Js.Nullable.t(int),
    
      /** Message to display in the body of the toast. */
    "message": ReasonReact.reactElement,

      /**
       * Callback invoked when the toast is dismissed, either by the user or by the timeout.
       * The value of the argument indicates whether the toast was closed because the timeout expired.
       */
    "onDismiss": Js.Nullable.t(ReasonReact.Callback.t(bool)),

      /**
       * Milliseconds to wait before automatically dismissing toast.
       * Providing a value less than or equal to 0 will disable the timeout (this is discouraged).
       * @default 5000
       */
    "timeout": Js.Nullable.t(int)
  };

  let create = 
        (
          ~message: ReasonReact.reactElement, 
          ~action: option(ActionProps.t)=?,
          ~intent: option(Intent.t)=?,
          ~iconName: option(string)=?, 
          ~onDismiss: option(ReasonReact.Callback.t(bool))=?, 
          ~timeout: option(int)=?,
          ()
        ) => {
          {
            "iconName": Js.Nullable.from_opt(iconName),
            "intent": Js.Nullable.from_opt(optionMap(Intent.toInt, intent)),
            "message": message,
            /* todo next ones need correct conversion */
            "action": Js.Nullable.from_opt(action),
            "onDismiss": Js.Nullable.from_opt(onDismiss),
            "timeout": Js.Nullable.from_opt(timeout)
          };
        };
};


module IToaster = {
  type t;
  /** Show a new toast to the user. Returns the unique key of the new toast. */
  [@bs.send] external show : (t, ToastProps.t) => string = "show";

  /**
   * Updates the toast with the given key to use the new props.
   * Updating a key that does not exist is effectively a no-op.
   */
  [@bs.send] external update : (t, string, ToastProps.t) => unit = "update" ;

  /** Dismiss the given toast instantly. */
  [@bs.send] external dismiss : (t, string) => unit = "dismiss" ;

  /** Dismiss all toasts instantly. */
  [@bs.send] external clear : (t) => unit = "clear" ;

  /** Returns the props for all current toasts. */
  /* TODO - ToastOptions are almost same as ToastProps
   * [@bs.send] external getToasts : (t) => Js.Array.t(ToastOptions.t) = "getToasts"; 
  */
};

module ToasterProps = {
  type t = {
    .
    "autoFocus": Js.Nullable.t(Js.boolean),
    "canEscapeKeyClear": Js.Nullable.t(Js.boolean),
    "className": Js.Nullable.t(string),
    "inline": Js.Nullable.t(Js.boolean),
    "position": Js.Nullable.t(int)
  };
  let create = 
      (
        ~autoFocus: option(bool)=?,
        ~canEscapeKeyClear: option(bool)=?,
        ~className: option(string)=?,
        ~inline: option(bool)=?,
        ~position: option(Position.t)=?,
        ()
      ) => {
        {
          "autoFocus": Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, autoFocus)),
          "canEscapeKeyClear": Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, canEscapeKeyClear)),
          "className": Js.Nullable.from_opt(className),
          "inline": Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, inline)),
          "position": Js.Nullable.from_opt(optionMap(Position.toInt, position))
        }
      }
};

module Toaster = {
  [@bs.module "@blueprintjs/core"][@bs.scope "Toaster"] external create : (ToasterProps.t) => IToaster.t = "";

  [@bs.module "@blueprintjs/core"] external reactClass : ReasonReact.reactClass = "Toaster";
  let make =
      (
        ~autoFocus: option(bool)=?,
        ~canEscapeKeyClear: option(bool)=?,
        ~className: option(string)=?,
        ~inline: option(bool)=?,
        ~position: option(Position.t)=?,
        ~_ref: option(ReasonReact.reactRef)=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props={
        "autoFocus": Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, autoFocus)),
        "canEscapeKeyClear":
          Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, canEscapeKeyClear)),
        "className": Js.Nullable.from_opt(className),
        "inline": Js.Nullable.from_opt(optionMap(Js.Boolean.to_js_boolean, inline)),
        "position": Js.Nullable.from_opt(optionMap(Position.toInt, position)),
        "ref": Js.Nullable.from_opt(_ref)
      },
      children
    );
};