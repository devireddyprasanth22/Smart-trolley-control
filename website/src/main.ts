import "./style.css";
import "./underlines";

const forwardButton = document.querySelector(".control_straight") as HTMLImageElement;
const leftButton = document.querySelector(".control_left") as HTMLImageElement;
const rightButton = document.querySelector(".control_right") as HTMLImageElement;
const backButton = document.querySelector(".control_back") as HTMLImageElement;
const allButtons = document.querySelectorAll(".controller_button") as NodeListOf<HTMLImageElement>;

enum Direction {
    Forward = "forward",
    Left = "left",
    Right = "right",
    Backward = "backward",
    Stop = "stop",
}

const removeHighlight = () => {
    allButtons.forEach((button) => {
        button.classList.remove("controller_active");
    });
};

function highlightButton(direction: Direction) {
    removeHighlight();
    switch (direction) {
        case Direction.Forward:
            forwardButton.classList.add("controller_active");
            break;
        case Direction.Left:
            leftButton.classList.add("controller_active");
            break;
        case Direction.Right:
            rightButton.classList.add("controller_active");
            break;
        case Direction.Backward:
            backButton.classList.add("controller_active");
            break;
    }
}

forwardButton.addEventListener("click", async () => {
    highlightButton(Direction.Forward);
    const response = await fetch("/direction/forward");
    console.log(response);
});

leftButton.addEventListener("click", async () => {
    highlightButton(Direction.Left);
    const response = await fetch("/direction/left");
    console.log(response);
});

rightButton.addEventListener("click", async () => {
    highlightButton(Direction.Right);
    const response = await fetch("/direction/right");
    console.log(response);
});

backButton.addEventListener("click", async () => {
    highlightButton(Direction.Backward);
    const response = await fetch("/direction/backward");
    console.log(response);
});
