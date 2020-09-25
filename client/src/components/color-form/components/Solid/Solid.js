import React from 'react';
import ColorSlider from '../../../color-slider/ColorSlider'
import ColorBox from '../../../color-box/ColorBox'

const MAX_COLORS = 10

class Solid extends React.Component {
	constructor(props) {
		super(props);

		this.state = {
			colors: Array(MAX_COLORS).fill([0, 0, 0]),
			numColors: 3,
			selectedColorIndex: 0,
			currentR: 0,
			currentG: 0,
			currentB: 0
		};
		
		this.props.onChange(this.state.colors, this.state.selectedColorIndex, null)

		this.onColorBoxClick = this.onColorBoxClick.bind(this);
		this.handleColorSlider = this.handleColorSlider.bind(this);
	}

	handleColorSlider(value, name) {
		this.setState({ ['current' + name]: value }, () => {
			this.setState(state => {
				let colors = state.colors;
				colors[state.selectedColorIndex] = [state.currentR, state.currentG, state.currentB];
				return({ colors });
			}, this.props.onChange(this.state.colors, this.state.selectedColorIndex, null));
		});
	}

	onColorBoxClick(id) {
		let index = parseInt(/\d+/.exec(id));
		this.setState({
			selectedColorIndex: index,
			currentR: this.state.colors[index][0],
			currentG: this.state.colors[index][1],
			currentB: this.state.colors[index][2],
		});

		this.props.onChange(this.state.colors, index, null);
	}

	render() {
		let colorBoxes = [];
		
		for(let i = 0; i < this.state.numColors; i++) {
			let color = `rgb(${this.state.colors[i][0]}, ${this.state.colors[i][1]}, ${this.state.colors[i][2]})`;
			colorBoxes.push(<ColorBox key={i} id={`color-box-${i}`} color={color} onClick={this.onColorBoxClick}></ColorBox>);
		}
		
		return (
			<div>
				<div className="sliders">
					<div>
						<ColorSlider name="R" value={this.state.currentR} onChange={this.handleColorSlider}></ColorSlider>
						<ColorSlider name="G" value={this.state.currentG} onChange={this.handleColorSlider}></ColorSlider>
						<ColorSlider name="B" value={this.state.currentB} onChange={this.handleColorSlider}></ColorSlider>
					</div>
				</div>
				<div className="color-selector">
					{colorBoxes}
				</div>
			</div>
		)
	}
}

export default Solid;