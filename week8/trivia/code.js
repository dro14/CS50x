$('button').click(function(event) {
    const id = event.target.id;
    if (id == 'option5')
    {
        $('#correctness1').css('color', 'green');
        $('#correctness1').html('Correct!');
        event.target.style.backgroundColor = 'lightGreen';
    }
    else if (id != '')
    {
        $('#correctness1').css('color', 'red');
        $('#correctness1').html('Incorrect');
        event.target.style.backgroundColor = 'lightCoral';
    }
});

document.querySelector('#question2').addEventListener('click', function()
{
    const answer = document.querySelector('#answer').value;
    if (answer == 'Tashkent')
    {
        document.querySelector('#answer').style.backgroundColor = 'lightGreen';
        document.querySelector('#correctness2').style = 'color:green';
        document.querySelector('#correctness2').innerHTML = 'Correct!';
    }
    else if (answer != '')
    {
        document.querySelector('#answer').style.backgroundColor = 'lightCoral';
        document.querySelector('#correctness2').style = 'color:red';
        document.querySelector('#correctness2').innerHTML = 'Incorrect';
    }
});