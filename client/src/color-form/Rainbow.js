import React from 'react';
import ColorSlider from '../color-slider/ColorSlider';

class Rainbow extends React.Component {
	constructor(props) {
		super(props);

		this.state = {
			speed: 50
		}

		this.handleSpeedSlider = this.handleSpeedSlider.bind(this);
	}

	handleSpeedSlider(value) {
		console.log('test1');
		this.setState({ speed: value });
		this.props.onChange([], value, null);
	}

	render() {
		return (
			<div className="sliders">
				<ColorSlider name="Speed" value={this.state.speed} onChange={this.handleSpeedSlider}></ColorSlider>
			</div>
		);
	}
}

export default Rainbow;