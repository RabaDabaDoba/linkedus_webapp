const express = require('express');
const mysql = require('mysql');
const bodyParser = require('body-parser');
const path = require('path');
const app = express();
const port = process.env.PORT || 5000;
const db = require('./db');

//Jessies version could work as well
const TEMPID = 1;


  app.use(bodyParser.urlencoded())
  app.use(bodyParser.json())

  app.post('/profile', function(req, res) {
    //console.log('posted to /profile');
    //console.log(req.body);
    //console.log(req.method);
    var addsql = 'INSERT IGNORE INTO user_info (name, photo, title, location, summary, saveActive) VALUES(?,?,?,?,?,0)';
    var sqlparams = [req.body.Name, req.body.pictureURL, req.body.headline, req.body.location, req.body.summary];
    db.query(addsql,sqlparams,function(err,result){
      if(err){
        console.log('[INSERT ERROR] -', err.message);
        return;
      }
      console.log('------INSERT--------');
      console.log(result);
      //console.log('--------------------\n\n');
    });
  });


//var addsql = 'INSERT IGNORE INTO user_info (name, photo, title, location, summary, saveActive) VALUES(?,?,?,?,?,0)';
//var sqlparams = [name, profile.pictureURL, profile.headline, profile.location, profile.summary];



/*db.query(addsql,sqlparams,function(err,result){
  if(err){
    console.log('[INSERT ERROR] -', err.message);
    return;
  }
  console.log('------INSERT--------');
  console.log('result');
  console.log('--------------------\n\n');
});
*/
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

// API calls
app.get('/api/userinfo', (req, res) => {
  db.query('SELECT * FROM user_info WHERE title = "CEO";', (err, results) => {
    if(err) return res.send(err);
    return res.json({
        data: results
    })
  })
});

app.get('/api/usersaved', (req, res) => {
  db.query('SELECT * FROM user_info WHERE saveActive = 1;',(err, results) => {
    if(err) return res.send(err);
    return res.json({
        data: results
    })
  })
});

app.get('/api/test', (req, res) => {
  db.query('SELECT * FROM user_info WHERE title = "CEO";',(err, results) => {
    if(err) return res.send(err);
    return res.json({
        data: results
    })
  })
});

app.get('/api/chats', (req, res) => {
  db.query('SELECT * FROM chat WHERE user_id_1 = ?;',TEMPID, (err, results) => {
    if(err) return res.send(err);
    return res.json({
        data: results
    })
  })
});

app.get('/api/messages', (req, res) => {
  db.query('SELECT * FROM message WHERE chat_id = ?', 1,(err, results) => {
    if(err) return res.send(err);
    return res.json({
        data: results
    })
  })
});

app.get('/api/name-chat', (req, res) => {
  db.query('SELECT name FROM user_info WHERE user_id = ?', 2,(err, results) => {
    if(err) return res.send(err);
    return res.json({
        data: results
    })
  })
});

app.post('/written-message', function(req, res) {
  var addsql = 'INSERT INTO message (from_id, to_id, chat_id, message) VALUES (?,?,?,?)';
  var sqlparams = [1,2,1,req.body.message];
  db.query(addsql,sqlparams,function(err,result){
    if(err){
      console.log('[INSERT ERROR] -', err.message);
      return;
    }
  });
});



if (process.env.NODE_ENV === 'production') {
  // Serve any static files
  app.use(express.static(path.join(__dirname, 'client/build')));
  // Handle React routing, return all requests to React app
  app.get('*', function(req, res) {
    res.sendFile(path.join(__dirname, 'client/build', 'index.html'));
  });
}
app.listen(port, () => console.log(`Listening on port ${port}`));
