var elementsWorthCopying = document.querySelectorAll(".copy-container .copy");
// Add click event listener for clicking the text
var styleSheetWrapperEl = document.getElementById('js-copy-container');
setTimeout(function() {
  document.getElementById("refresh").classList.remove('hide')
},5000);

styleSheetWrapperEl.addEventListener('click', function (e) {
  if (e.target.className !== 'copy') return;
  var element = e.target;
  copyText(element);
  setTimeout(arguments.callee, 3000);
});
// Main functionality
function copyText(element) {
  var textToCopy = element.innerText;
  var myTemporaryInputElement = document.createElement("input");
  myTemporaryInputElement.type = "text";
  myTemporaryInputElement.value = textToCopy;
  document.body.appendChild(myTemporaryInputElement);
  myTemporaryInputElement.select();
  document.execCommand("Copy");
  document.body.removeChild(myTemporaryInputElement);
}