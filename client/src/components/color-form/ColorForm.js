import React from 'react';
import './ColorForm.css';
import ModeSelector from '../mode-selector/ModeSelector';
import ColorSlider from '../color-slider/ColorSlider';
import Solid from './components/Solid/Solid';
import Rainbow from './components/Rainbow/Rainbow';

import { submitColorForm } from '../../services/api';

class ColorForm extends React.Component {
	constructor(props) {
		super(props);

		// TODO: get colors from backend

		this.state = {
			mode: 1,
			colors: null,
			param1: null,
			param2: null,
			brightness: 100
		};

		this.handleSubmit = this.handleSubmit.bind(this);
		this.handleModeChange = this.handleModeChange.bind(this);
		this.handleBrightnessChange = this.handleBrightnessChange.bind(this);
		this.handleFormChange = this.handleFormChange.bind(this);
	}
	
	handleSubmit(event) {
		event.preventDefault();

		console.log({
			mode: this.state.mode,
			brightness: this.state.brightness,
			colors: this.state.colors,
			param1: this.state.param1,
			param2: this.state.param2
		});

		submitColorForm(this.state.mode, this.state.brightness, this.state.colors);
	}

	handleModeChange(mode) {
		this.setState({ mode });
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
				<ModeSelector onChange={this.handleModeChange}></ModeSelector>
				<Solid onChange={this.handleFormChange}></Solid>
				<Rainbow onChange={this.handleFormChange}></Rainbow>
				<ColorSlider name="Brightness" value={this.state.brightness} onChange={this.handleBrightnessChange}></ColorSlider>
				<input type="submit" value="Submit"></input>
			</form>
		);
	}
}

export default ColorForm;
