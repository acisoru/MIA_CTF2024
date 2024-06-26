document.getElementById('form').addEventListener('submit', event => {
	event.preventDefault();

	fetch('/api/submit', {
		method: 'POST',
		body: JSON.stringify({
			'secret.name': document.querySelector('input[type=text]').value
		}),

		headers: {'Content-Type': 'application/json'}
	}).then(resp => {
		return resp.json();
	}).then(data => {
		document.getElementById('output').innerHTML = data.response;
	});

});