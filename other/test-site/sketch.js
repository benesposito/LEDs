function setup() {
	createCanvas(16000, 200);
	frameRate(5);
}

let i = 0;
function draw() {
	background(220);
	
	let leds = simulation[i];
	for(let j = 0; j < leds.length; j++) {
		fill(leds[j % leds.length])
		circle(70 + 50 * j, 50, 40);
	}

	console.log(i);
	i++;
	if(i >= simulation.length)
		i = 0;
}
