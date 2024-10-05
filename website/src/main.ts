import "./style.css";

const forwardButton = document.querySelector(".control_straight") as HTMLImageElement;
const leftButton = document.querySelector(".control_left") as HTMLImageElement;
const rightButton = document.querySelector(".control_right") as HTMLImageElement;
const backButton = document.querySelector(".control_back") as HTMLImageElement;

forwardButton.addEventListener("click", () => {
    console.log("forward");
});

leftButton.addEventListener("click", () => {
    console.log("left");
});

rightButton.addEventListener("click", () => {
    console.log("right");
});

backButton.addEventListener("click", () => {
    console.log("back");
});
