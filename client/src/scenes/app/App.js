import React from 'react';
import './App.css';
import ColorForm from '../../components/color-form/ColorForm';
import Enabler from '../../components/enabler/Enabler';
import ModeSelector from '../../components/mode-selector/ModeSelector';

function App() {
  return (
    <div className="App">
		<Enabler></Enabler>
		<ModeSelector></ModeSelector>
    </div>
  );
}

export default App;
