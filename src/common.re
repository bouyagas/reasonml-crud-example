module Request = {
  let defaultHeaders = [%bs.raw {|
    {
      "Content-Type": "application/json"
    }
  |}];
  let getDefaultHeaders = () => Fetch.HeadersInit.make(defaultHeaders);
};

exception FetchError(Fetch.response);

module Response = {
  let statusOk = (response) =>
    Fetch.Response.ok(response) ? Js.Promise.resolve() : Js.Promise.reject(FetchError(response));
};