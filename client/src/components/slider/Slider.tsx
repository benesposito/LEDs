import React, { ChangeEvent, useState } from 'react';
import './Slider.css';

type Props = {
	label: string,
	min: number,
	max: number,
	value: number,
	showBorder: boolean
}

const defaultProps: Props = {
	label: '',
	min: 0,
	max: 255,
	value: 0,
	showBorder: true
}

function Slider(props: Props) {
	const [value, setValue] = useState(props.value);

	let classNames = ['slider'];

	if(+props.showBorder)
		classNames.push('slider-border');
	
	function handleChange(event: ChangeEvent<HTMLInputElement>) {
		setValue(+event.target.value);
	}

	return (
		<div>
			<label className={classNames.join(' ')}>
				<span>{props.label}</span>
				<input
					type="range"
					min={props.min}
					max={props.max}
					value={value}
					onChange={handleChange} >
				</input>
			</label>
		</div>
	);
}

Slider.defaultProps = defaultProps;

export default Slider;