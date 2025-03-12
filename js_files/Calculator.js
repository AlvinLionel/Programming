document.addEventListener("DOMContentLoaded", function () {
    const output = document.getElementById("output");
    const buttons = document.querySelectorAll(".calculator__button");

    buttons.forEach(button => {
        button.addEventListener("click", () => {
            const buttonValue = button.innerText;
            if (buttonValue == '=') {
                try {
                    output.innerText = eval(output.innerText);
                }
                catch {
                    output.innerText = 'error';
                }
            }
            else if (buttonValue == 'C') {
                output.innerText = '';
            }
            else if (buttonValue === '+/-') {
                if (output.innerText.charAt(0) === '-') {
                    output.innerText = output.innerText.substring(1);
                } else {
                    output.innerText = '-' + output.innerText;
                }
            }
            else {
                output.innerText += buttonValue;
            }
        });
    });
});