import React from 'react';
import './ColorBox.css';

class ColorBox extends React.Component {
	constructor(props) {
		super(props);

		this.handleOnClick = this.handleOnClick.bind(this);
	}

	handleOnClick(event) {
		this.props.onClick(this.props.id);
	}

	render() {
		return (
			<div className="color-box" style={{backgroundColor: this.props.color}} onClick={this.handleOnClick}>
				
			</div>
		);
	}
}

export default ColorBox;