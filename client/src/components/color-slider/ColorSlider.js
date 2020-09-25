import React from 'react';
import './ColorSlider.css';

class ColorSlider extends React.Component {
	constructor(props) {
		super(props);

		this.state = { value: 0 };

		this.handleChange = this.handleChange.bind(this);
	}

	static getDerivedStateFromProps(props, currentState) {
		return({
			value: props.value
		});
	}

	handleChange(event) {
		let value = parseInt(event.target.value);

		if(!value)
			value = 0;
		else if (value > 255)
			value = 255;

		this.props.onChange(value, this.props.name);
		this.setState({ value });
	}
	
	render() {
		return (
			<div className="color-slider">
				<span>
					<label htmlFor={this.props.name + "-range"}>{this.props.name}</label>
					<input type="range" min="0" max="255" value={this.state.value} name={this.props.name + "-range"} onChange={this.handleChange}></input>
					<input type="text" name={this.props.name + "-number"} value={this.state.value} onChange={this.handleChange}></input>
				</span>
			</div>
		);
	}
}

export default ColorSlider;