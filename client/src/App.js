import React from 'react';
import logo from './logo.svg';
import './App.css';

function App() {
  return (
    <div className="App">
		<ColorForm></ColorForm>
    </div>
  );
}

class ColorForm extends React.Component {
	constructor(props) {
		super(props);

		this.state = {
			enabled: false,
			R: 0,
			G: 0,
			B: 0
		};

		this.handleFieldChange = this.handleFieldChange.bind(this);
		this.handleSubmit = this.handleSubmit.bind(this);
		this.handleEnable = this.handleEnable.bind(this);
	}

	handleFieldChange(fieldId, value) {
		this.setState({ [fieldId]: value });
	}
	
	handleSubmit(event) {
		event.preventDefault();

		fetch('http://10.250.73.241:5000/submit', {
			method: 'POST',
			headers: {
				Accept: 'application/json',
				'Content-Type': 'application/json'
			},
			body: JSON.stringify({
				mode: 3,
				colors: [[this.state.R, this.state.G, this.state.B]]
			})
		}).then(res => {
			console.log(res);
		});

		console.log(this.state);
	}

	handleEnable(event) {
		this.setState({enabled: !this.state.enabled});

		fetch('http://10.250.73.241:5000/toggle', {
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
	}
	
	render() {
		return (
			<form onSubmit={this.handleSubmit}>
				<input className="toggle-button" type="button" value={this.state.enabled? "On" : "Off"} onClick={this.handleEnable}></input>
				<ColorSlider value="R" onChange={this.handleFieldChange}></ColorSlider>
				<ColorSlider value="G" onChange={this.handleFieldChange}></ColorSlider>
				<ColorSlider value="B" onChange={this.handleFieldChange}></ColorSlider>
				<input type="submit" value="Submit"></input>
			</form>
		);
	}
}

class ColorSlider extends React.Component {
	constructor(props) {
		super(props);

		this.state = { value: 0 };

		this.handleChange = this.handleChange.bind(this);
	}

	handleChange(event) {
		let val = parseInt(event.target.value);
		
		if(val > 255)
			val = 255;
		
		this.props.onChange(this.props.value, val);
		this.setState({ value: val });
	}
	
	render() {
		return (
			<div className="color-slider">
				<span>
					<label htmlFor={this.props.value + "-range"}>{this.props.value}</label>
					<input type="range" min="0" max="255" value={this.state.value} name={this.props.value + "-range"} onChange={this.handleChange}></input>
					<input type="text" name={this.props.value + "-number"} value={this.state.value} onChange={this.handleChange}></input>
				</span>
			</div>
		);
	}
}

export default App;
