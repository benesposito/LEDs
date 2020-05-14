import React from 'react';
import './ColorForm.css';
import ModeSelector from '../mode-selector/ModeSelector';
import Solid from './Solid';
import ColorSlider from '../color-slider/ColorSlider';

const IP = '10.0.0.191';

class ColorForm extends React.Component {
	constructor(props) {
		super(props);

		// TODO: get colors from backend

		this.state = {
			mode: 1,
			colors: undefined,
			brightness: 100
		};

		this.handleSubmit = this.handleSubmit.bind(this);
		this.handleBrightnessChange = this.handleBrightnessChange.bind(this);
		this.handleFormChange = this.handleFormChange.bind(this);
	}
	
	handleSubmit(event) {
		event.preventDefault();

		fetch(`http://${IP}:5000/submit`, {
			method: 'POST',
			headers: {
				Accept: 'application/json',
				'Content-Type': 'application/json'
			},
			body: JSON.stringify({
				mode: this.state.mode,
				brightness: this.state.brightness,
				colors: this.state.colors,
				param1: this.state.param1,
				param2: this.state.param2
			})
		}).then(res => {
			console.log(res);
		});
	}

	handleBrightnessChange(value) {
		this.setState({ brightness: value });
	}
	
	handleFormChange(colors, param1, param2) {
		this.setState({ colors, param1, param2 });
	}
	
	render() {
		return (
			<form onSubmit={this.handleSubmit}>
				<ModeSelector></ModeSelector>
				<Solid onChange={this.handleFormChange}></Solid>
				<ColorSlider name="Brightness" value={this.state.brightness} onChange={this.handleBrightnessChange}></ColorSlider>
				<input type="submit" value="Submit"></input>
			</form>
		);
	}
}

export default ColorForm;