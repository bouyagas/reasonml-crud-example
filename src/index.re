open Utils;

requireCSS("./index.css");

registerServiceWorker();

ReactDOMRe.renderToElementWithId(<App />, "root");