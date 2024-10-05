import "./style.css";

const forwardButton = document.querySelector(".control_straight") as HTMLImageElement;
const leftButton = document.querySelector(".control_left") as HTMLImageElement;
const rightButton = document.querySelector(".control_right") as HTMLImageElement;
const backButton = document.querySelector(".control_back") as HTMLImageElement;

forwardButton.addEventListener("click", async () => {
    const response = await fetch("/direction/forward");
    console.log(response);
});

leftButton.addEventListener("click", async () => {
    const response = await fetch("/direction/left");
    console.log(response);
});

rightButton.addEventListener("click", async () => {
    const response = await fetch("/direction/right");
    console.log(response);
});

backButton.addEventListener("click", async () => {
    await fetch("/direction/back");
    console.log("back");
});
