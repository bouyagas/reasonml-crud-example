open Utils;

requireCSS("./index.css");

registerServiceWorker();

let renderForRoute = (route: Routing.route) =>
  ReactDOMRe.renderToElementWithId(<App route />, "root");

Routing.init(renderForRoute);