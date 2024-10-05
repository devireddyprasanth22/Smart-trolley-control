import "./style.css";

const forwardButton = document.querySelector(".control_straight") as HTMLImageElement;
const leftButton = document.querySelector(".control_left") as HTMLImageElement;
const rightButton = document.querySelector(".control_right") as HTMLImageElement;
const backButton = document.querySelector(".control_back") as HTMLImageElement;

forwardButton.addEventListener("click", async () => {
    await fetch("/direction/forward");
});

leftButton.addEventListener("click", async () => {
    await fetch("/direction/left");
});

rightButton.addEventListener("click", async () => {
    await fetch("/direction/right");
});

backButton.addEventListener("click", async () => {
    await fetch("/direction/back");
});
