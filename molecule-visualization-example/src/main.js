import * as THREE from "three";

import { PDBLoader } from "three/addons/loaders/PDBLoader.js";
import { addGuiParams, DEFAULT_MOLECULE, DEFAULT_SCALING } from "./parameters";
import GUI from "three/addons/libs/lil-gui.module.min.js";
import {
  addToScene,
  initControls,
  initRenderer,
  initScene,
  initWindowResizeHandling,
  clearScene,
} from "./general";

let scaling = DEFAULT_SCALING;
let modelUrl = getUrlFor(DEFAULT_MOLECULE);

function getUrlFor(molecule) {
  return "/models/" + molecule;
}

const pdbLoader = new PDBLoader();
const offset = new THREE.Vector3();
const boxGeometry = new THREE.BoxGeometry(1, 1, 1);
const sphereGeometry = new THREE.IcosahedronGeometry(1, 3);

init();

function init() {
  initScene();
  initRenderer();
  initControls();
  reloadMolecule();
  initGui();
  initWindowResizeHandling();
}

function initGui() {
  const gui = new GUI();
  addGuiParams(gui, setModel, setScaling);
  gui.open();
}

function setScaling(s) {
  scaling = s;
  reloadMolecule();
}

function setModel(model) {
  modelUrl = getUrlFor(model);
  reloadMolecule();
}

function reloadMolecule() {
  clearScene();

  pdbLoader.load(modelUrl, function (pdb) {
    const geometryAtoms = pdb.geometryAtoms;
    const geometryBonds = pdb.geometryBonds;
    computeBoundingBox(geometryAtoms, geometryBonds);

    const atomPositions = geometryAtoms.getAttribute("position");
    const colors = geometryAtoms.getAttribute("color");
    drawAtoms(atomPositions, colors);

    drawBonds(geometryBonds.getAttribute("position"));
  });
}

function drawAtoms(atomPositions, colors) {
  for (let i = 0; i < atomPositions.count; i++) {
    const atomPosition = getAtomPosition(atomPositions, i);
    const color = getAtomColor(colors, i);
    const material = new THREE.MeshPhongMaterial({ color: color });
    const atomObject = createAtomObject(material, atomPosition);
    addToScene(atomObject);
  }
}

function computeBoundingBox(geometryAtoms, geometryBonds) {
  geometryAtoms.computeBoundingBox();
  geometryAtoms.boundingBox.getCenter(offset).negate();
  geometryAtoms.translate(offset.x, offset.y, offset.z);
  geometryBonds.translate(offset.x, offset.y, offset.z);
}

const _reusableColor = new THREE.Color();

function getAtomColor(atomColors, i) {
  _reusableColor.r = atomColors.getX(i);
  _reusableColor.g = atomColors.getY(i);
  _reusableColor.b = atomColors.getZ(i);
  return _reusableColor;
}

const _reusablePosition = new THREE.Vector3();

function getAtomPosition(atomPositions, i) {
  _reusablePosition.x = atomPositions.getX(i) * scaling;
  _reusablePosition.y = atomPositions.getY(i) * scaling;
  _reusablePosition.z = atomPositions.getZ(i) * scaling;
  return _reusablePosition;
}

function createAtomObject(material, atomPosition) {
  const atomObject = new THREE.Mesh(sphereGeometry, material);
  atomObject.position.copy(atomPosition);
  atomObject.position.multiplyScalar(75);
  atomObject.scale.multiplyScalar(25);
  return atomObject;
}

function drawBonds(bondPositions) {
  for (let i = 0; i < bondPositions.count; i += 2) {
    const [start, end] = getBondStartEnd(bondPositions, i);
    addToScene(createBondObject(start, end));
  }
}

const _start = new THREE.Vector3();
const _end = new THREE.Vector3();

function getBondStartEnd(bondPositions, i) {
  _start.x = bondPositions.getX(i) * scaling;
  _start.y = bondPositions.getY(i) * scaling;
  _start.z = bondPositions.getZ(i) * scaling;

  _end.x = bondPositions.getX(i + 1) * scaling;
  _end.y = bondPositions.getY(i + 1) * scaling;
  _end.z = bondPositions.getZ(i + 1) * scaling;

  _start.multiplyScalar(75);
  _end.multiplyScalar(75);
  return [_start, _end];
}

function createBondObject(start, end) {
  const bondObject = new THREE.Mesh(
    boxGeometry,
    new THREE.MeshPhongMaterial({ color: 0xffffff })
  );
  bondObject.position.copy(start);
  bondObject.position.lerp(end, 0.5);
  bondObject.scale.set(5, 5, start.distanceTo(end));
  bondObject.lookAt(end);
  return bondObject;
}
