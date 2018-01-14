open Blueprintjs;

let toasterProps = ToasterProps.create(~position=Position.BOTTOM, ());

let toaster = Toaster.create(toasterProps);

let showError = (text) => {
  let props =
    ToastProps.create(
      ~message=Utils.textEl(text),
      ~iconName="warning-sign",
      ~intent=Intent.DANGER,
      ()
    );
  IToaster.show(toaster, props)
};