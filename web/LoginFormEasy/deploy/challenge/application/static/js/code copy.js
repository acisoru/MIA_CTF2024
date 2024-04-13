document.getElementById('log_form').addEventListener('submit', function(e) {
  e.preventDefault();

  var email = document.getElementById('email').value;
  var password = document.getElementById('password').value;

  fetch("/login", {
    method: "POST",
    body: JSON.stringify({
      email: email,
      password: password
    }),
    headers: {
      "Content-type": "application/json"
    }
  })
});
