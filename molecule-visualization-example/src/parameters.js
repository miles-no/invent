// Parameters for the molecule visualization example
// We export everything here, just keep the parameters in one place
const MOLECULES = {
  Absolut: "absolut.pdb",
  Ethanol: "ethanol.pdb",
  Caffeine: "caffeine.pdb",
  Graphite: "graphite.pdb",
};

const SCALING_OPTIONS = {
  1: 1,
  2: 2,
  3: 3,
  5: 5,
  8: 8,
};

const DEFAULT_SCALING = 8;
const DEFAULT_MOLECULE = "absolut.pdb";

const params = {
  molecule: DEFAULT_MOLECULE,
  scaling: DEFAULT_SCALING,
};

function addGuiParams(gui, setModel, setScaling) {
  gui.add(params, "molecule", MOLECULES).onChange(setModel);
  gui.add(params, "scaling", SCALING_OPTIONS).onChange(setScaling);
}

export { DEFAULT_MOLECULE, DEFAULT_SCALING, addGuiParams };
