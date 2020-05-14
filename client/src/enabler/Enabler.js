import React from 'react';

const IP = '10.0.0.191';

class Enabler extends React.Component {
	constructor(props) {
		super(props);

		this.state = {
			enabled: false
		};

		this.handleEnable = this.handleEnable.bind(this);
	}

	handleEnable(event) {
		this.setState({enabled: !this.state.enabled}, () => {
			fetch(`http://${IP}:5000/toggle`, {
				method: 'POST',
				headers: {
					Accept: 'application/json',
					'Content-Type': 'application/json'
				},
				body: JSON.stringify({
					enabled: this.state.enabled
				})
			}).then(res => {
				console.log(res);
			});
		});
	}

	render() {
		return (	
			<input className="toggle-button" type="button" value={this.state.enabled? "On" : "Off"} onClick={this.handleEnable}></input>
		);
	}
}

export default Enabler;