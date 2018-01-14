const express = require('express');
const bodyParser = require('body-parser');
const clients = require('./clients');
const app = express();
const port = process.env.PORT || 3001;


app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());


app.route('/api/clients')
  .get(clients.getAll)
  .post(clients.create);

app.route('/api/clients/:clientId')
  .get(clients.get)
  .put(clients.update)
  .delete(clients.remove);


app.use(function (req, res) {
  res.status(404).send({ url: req.originalUrl + ' not found' })
});

app.listen(port);

console.log('ReasonML CRUD example API server started on: ' + port);
