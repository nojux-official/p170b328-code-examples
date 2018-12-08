document.addEventListener('DOMContentLoaded', () => {
    const button = document.getElementById("button");
    button.addEventListener("click", event => {
        event.target.innerText = "I am clicked";
    })
});