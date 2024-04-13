document.getElementById('log_form').addEventListener('submit', function(e) {
  e.preventDefault();

  var email = document.getElementById('email').value;
  var password = document.getElementById('password').value;

  var jsonData = {
    email: email,
    password: password
  };

  var xhr = new XMLHttpRequest();
  xhr.open('POST', '/login', true);
  xhr.setRequestHeader('Content-Type', 'application/json');
  xhr.send(JSON.stringify(jsonData));
});