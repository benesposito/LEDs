import React from 'react';
import './App.css';
import ColorForm from './color-form/ColorForm';
import Enabler from './enabler/Enabler';

function App() {
  return (
    <div className="App">
		<Enabler></Enabler>
		<ColorForm></ColorForm>
    </div>
  );
}

export default App;
