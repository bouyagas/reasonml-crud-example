const loki = require('lokijs');
const db = new loki('database.json');

function loadCollection(colName, callback) {
  db.loadDatabase({}, function () {
    let col = db.getCollection(colName);

    if (!col) {
      console.log("Collection %s does not exit. Creating ...", colName);
      col = db.addCollection('clients');
    }

    callback(col);
  });
}

exports.getAll = (req, res) => {
  loadCollection('clients', (clients) => {
    console.log("Getting all clients", clients.data);
    res.json(clients.data);
  });
}
exports.get = (req, res) => {
  loadCollection('clients', (clients) => {
    const id = parseInt(req.params.clientId);
    console.log("Get client", id);
    const client = clients.findOne({ id: id });
    res.json(client);
  });
}
exports.create = (req, res) => {
  loadCollection('clients', (clients) => {
    const obj = req.body;
    obj.id = getNextId(clients.data);
    console.log("Inserting client", obj);
    const client = clients.insert(obj);
    db.saveDatabase();
    res.json(client);
  });
}
exports.update = (req, res) => {
  loadCollection('clients', (clients) => {
    const id = parseInt(req.params.clientId);
    console.log("Updating client with id", id);
    const client = clients.findOne({ id: id });
    client.name = req.body.name;
    clients.update(client);
    db.saveDatabase();
    res.sendStatus(200);
  });
}
exports.remove = (req, res) => {
  loadCollection('clients', (clients) => {
    const id = parseInt(req.params.clientId);
    console.log("Removing client with id", id);
    const client = clients.findOne({ id: id });
    clients.remove(client);
    db.saveDatabase();
    res.sendStatus(200);
  });
}


function getNextId(clientsData) {
  let id = 1;
  if (clientsData && clientsData.length > 0) {
    let ids = clientsData.map(c => c.id);
    let max = Math.max(...ids);
    console.log("next id", max, ids);
    id = max + 1;
  }
  return id;
}