import React from 'react';
import './ModeSelector.css';

class ModeSelector extends React.Component {
	constructor(props) {
		super(props);

		this.handleModeUpdate = this.handleModeUpdate.bind(this);
	}

	handleModeUpdate(event) {
		this.props.onChange(event.target.value);
	}

	render() {
		return (
			<div className="mode-selector">
				<label><input type="radio" name="mode" value="1" onClick={this.handleModeUpdate} defaultChecked></input>Solid</label>
				<label><input type="radio" name="mode" value="2" onClick={this.handleModeUpdate}></input>Rainbow</label>
			</div>
		);
	}
}

export default ModeSelector;