import React from 'react';
import './App.css';
import ColorForm from '../../components/color-form/ColorForm';
import Enabler from '../../components/enabler/Enabler';

function App() {
  return (
    <div className="App">
		<Enabler></Enabler>
		<ColorForm></ColorForm>
    </div>
  );
}

export default App;
