import React from 'react';
import { setEnabled } from '../../services/api';

class Enabler extends React.Component {
	constructor(props) {
		super(props);

		this.state = {
			enabled: false
		};

		this.handleEnable = this.handleEnable.bind(this);
	}

	handleEnable(event) {
		this.setState({enabled: !this.state.enabled}, () => setEnabled(this.state.enabled));
	}

	render() {
		return (
			<input className="toggle-button" type="button" value={this.state.enabled? "On" : "Off"} onClick={this.handleEnable}></input>
		);
	}
}

export default Enabler;