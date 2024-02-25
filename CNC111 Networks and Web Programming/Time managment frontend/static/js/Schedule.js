window.onload = () => {
  document.getElementById("submitBTN").onclick = createNewItem;
};

function createNewItem() {
  var title = document.getElementById("titleTB").value;
  var description = document.getElementById("descriptionTA").value;
  if (title == "") {
    alert("You must specifiy a title!");
    return;
  }
  isUrgent = document.getElementById("UCB").checked;
  isImportant = document.getElementById("ICB").checked;
  var scheduleList = document.getElementById("schedule-list");

  var newItem = document.createElement("li");

  var priority;
  if (isUrgent && isImportant) {
    priority = "IU";
  } else if (isUrgent && !isImportant) {
    priority = "NIU";
  } else if (!isUrgent && isImportant) {
    priority = "INU";
  } else if (!isUrgent && !isImportant) {
    priority = "NINU";
  }

  newItem.classList.add("schedule-item", priority);

  var newTitle = document.createElement("span");
  newTitle.innerHTML = title;

  var newRBTN = document.createElement("button");
  newRBTN.textContent = "X";
  newRBTN.classList.add("remove-item-btn");
  newRBTN.addEventListener("click", () => {
    scheduleList.removeChild(newItem);
  });

  if (description != "") {
    var newDescription = document.createElement("p");
    newDescription.textContent = description;
    newDescription.classList.add("schedule-item-desc");
  }
  newItem.appendChild(newTitle);
  newItem.appendChild(newRBTN);
  if (description) {
    newItem.appendChild(newDescription);
  }
  scheduleList.appendChild(newItem);
}
