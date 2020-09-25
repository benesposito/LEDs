const IP = '10.185.249.171';

function post(route, body) {
	fetch(`http://${IP}:5000/${route}`, {
		method: 'POST',
		headers: {
			Accept: 'application/json',
			'Content-Type': 'application/json'
		},
		body: JSON.stringify(body)
	}).then(res => console.log(res));
}

export function setEnabled(enabled) {
	post('setEnabled', { enabled });
}

export function submitColorForm(mode, brightness, colors) {
	post('submitColorForm', { mode, brightness, colors });
}