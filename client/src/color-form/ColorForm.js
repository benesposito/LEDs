import React from 'react';
import ColorSlider from '../color-slider/ColorSlider'
import ColorBox from '../color-box/ColorBox'

const IP = '10.0.0.191'

class ColorForm extends React.Component {
	constructor(props) {
		super(props);

		this.state = {
			enabled: false,
			mode: 1,
			numColors: 1,
			colors: [[0, 0, 0]],
			selectedColorBox: 0,
			r: 0,
			g: 0,
			b: 0,
			brightness: 100
		};

		this.handleColorSlider = this.handleColorSlider.bind(this);
		this.handleSubmit = this.handleSubmit.bind(this);
		this.handleEnable = this.handleEnable.bind(this);
		this.onColorBoxClick = this.onColorBoxClick.bind(this);
		this.handleModeUpdate = this.handleModeUpdate.bind(this);
		this.addColor = this.addColor.bind(this);
		this.removeColor = this.removeColor.bind(this);
	}

	handleColorSlider(fieldId, value) {
		this.setState({ [fieldId.toLowerCase()]: value }, () => {
			this.setState(state => {
				let colors = state.colors;
				colors[state.selectedColorBox] = [state.r, state.g, state.b];
				return({ colors });
			});
		});
	}
	
	handleSubmit(event) {
		event.preventDefault();

		fetch(`http://'${IP}:5000/submit`, {
			method: 'POST',
			headers: {
				Accept: 'application/json',
				'Content-Type': 'application/json'
			},
			body: JSON.stringify({
				mode: this.state.mode,
				colors: this.state.colors,
				brightness: this.state.brightness
			})
		}).then(res => {
			console.log(res);
		});
	}

	handleEnable(event) {
		this.setState({enabled: !this.state.enabled}, () => {
			fetch(`http://'${IP}:5000/toggle`, {
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

	onColorBoxClick(index) {
		this.setState({
			selectedColorBox: index,
			r: this.state.colors[index][0],
			g: this.state.colors[index][1],
			b: this.state.colors[index][2],
		});
	}

	handleModeUpdate(event) {
		this.setState({ mode: event.target.value });
	}

	addColor() {
		this.setState(state => {
			let colors = state.colors;
			colors.push([0, 0, 0]);

			return ({ numColors: this.state.numColors + 1, colors });
		});
	}

	removeColor() {
		this.setState(state => {
			let colors = state.colors;
			colors.pop();

			let numColors = this.state.numColors > 0? this.state.numColors - 1 : 0;

			return ({ numColors, colors });
		});
	}
	
	render() {
		let rgbStrings = [];

		for(let color of this.state.colors)
			rgbStrings.push(`rgb(${color[0]}, ${color[1]}, ${color[2]})`);

		return (
			<form onSubmit={this.handleSubmit}>
				<input className="toggle-button" type="button" value={this.state.enabled? "On" : "Off"} onClick={this.handleEnable}></input>
				<div className="mode-selector">
					<label><input type="radio" name="mode" value="1" onClick={this.handleModeUpdate} defaultChecked></input>Solid</label>
					<label><input type="radio" name="mode" value="2" onClick={this.handleModeUpdate}></input>Rainbow</label>
				</div>
				<div className="sliders">
					<div>
						<ColorSlider name="R" value={this.state.r} onChange={this.handleColorSlider}></ColorSlider>
						<ColorSlider name="G" value={this.state.g} onChange={this.handleColorSlider}></ColorSlider>
						<ColorSlider name="B" value={this.state.b} onChange={this.handleColorSlider}></ColorSlider>
					</div>
					<div>
						<ColorSlider name="Brightness" value={this.state.brightness} onChange={this.handleColorSlider}></ColorSlider>
					</div>
				</div>
				<div className="color-selector">
					{[...Array(this.state.numColors).keys()].map(i => <ColorBox key={i} id={`color-box-${i+1}`} style={{backgroundColor: rgbStrings[i]}} onClick={this.onColorBoxClick}></ColorBox>)}
					<input type="button" className="add-color-button" value="+" onClick={this.addColor}></input>
					<input type="button" className="add-color-button" value="-" onClick={this.removeColor}></input>
				</div>
				<input type="submit" value="Submit"></input>
			</form>
		);
	}
}

export default ColorForm;