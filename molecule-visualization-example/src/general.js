// General Three.JS stuff which is not PDF or molecule-specific

import { TrackballControls } from "three/addons/controls/TrackballControls";
import * as THREE from "three";

let root;
let controls;
let camera, scene, renderer;

/**
 * Initializes the Three.js controls - zoom with mouse wheel, rotate with mouse drag.
 */
function initControls() {
  controls = new TrackballControls(camera, renderer.domElement);
  controls.minDistance = 500;
  controls.maxDistance = 2000;
}

/**
 * Initializes the Three.js scene.
 */
function initScene() {
  scene = new THREE.Scene();
  scene.background = new THREE.Color(0x050505);

  camera = new THREE.PerspectiveCamera(
    70,
    window.innerWidth / window.innerHeight,
    1,
    5000
  );
  camera.position.z = 1000;
  scene.add(camera);

  const light1 = new THREE.DirectionalLight(0xffffff, 2.5);
  light1.position.set(1, 1, 1);
  scene.add(light1);

  const light2 = new THREE.DirectionalLight(0xffffff, 1.5);
  light2.position.set(-1, -1, 1);
  scene.add(light2);

  root = new THREE.Group();
  scene.add(root);
}

/**
 * Initializes the Three.js renderer.
 */
function initRenderer() {
  renderer = new THREE.WebGLRenderer({ antialias: true });
  renderer.setPixelRatio(window.devicePixelRatio);
  renderer.setSize(window.innerWidth, window.innerHeight);
  renderer.setAnimationLoop(animate);
  document.getElementById("container").appendChild(renderer.domElement);
}

/**
 * Initializes the window-resize event handling.
 */
function initWindowResizeHandling() {
  window.addEventListener("resize", onWindowResize);
}

/**
 * Adds an object to the scene.
 *
 * @param {THREE.Object3D} object3d The object to add.
 */
function addToScene(object3d) {
  root.add(object3d);
}

/**
 * Removes all current elements from the scene.
 */
function clearScene() {
  while (root.children.length > 0) {
    const object = root.children[0];
    object.parent.remove(object);
  }
}

function onWindowResize() {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();

  renderer.setSize(window.innerWidth, window.innerHeight);
}

function animate() {
  controls.update();

  const time = Date.now() * 0.0004;

  root.rotation.x = time;
  root.rotation.y = time * 0.7;

  render();
}

function render() {
  renderer.render(scene, camera);
}

export {
  initScene,
  initRenderer,
  initControls,
  initWindowResizeHandling,
  clearScene,
  addToScene,
};
