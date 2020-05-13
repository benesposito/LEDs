import React from 'react';

class ColorBox extends React.Component {
	constructor(props) {
		super(props);

		this.onClick = this.onClick.bind(this);
	}

	onClick(event) {
		this.props.onClick(parseInt(/.*(\d{1})/.exec(this.props.id)[1]) - 1);
	}

	render() {
		return (
			<div className="color-box" style={this.props.style} onClick={this.onClick}>
				
			</div>
		);
	}
}

export default ColorBox;