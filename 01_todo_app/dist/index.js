const projectName = "weekly-project-todo-app";
const trashCan = "";
const pencil = "";
const todos = [];
const storedText = localStorage.getItem(projectName);
if (storedText) {
    try {
        const storedTodos = JSON.parse(storedText);
        storedTodos.forEach((todo) => {
            todos.push(todo);
            createTodoElement(todo);
        });
    }
    catch (error) {
        console.error("Error loading todos from localStorage:", error);
    }
}
const todoForm = document.querySelector(".todo-form");
if (!todoForm) {
    throw new Error("todo-form is not defined");
}
todoForm.addEventListener("submit", submitTodo);
function submitTodo(e) {
    e.preventDefault();
    const todoInput = todoForm?.querySelector(".todo-input");
    if (!todoInput) {
        throw new Error("todo-input is not defined");
    }
    const text = todoInput.value.trim();
    if (!text) {
        return;
    }
    const newTodo = {
        id: crypto.randomUUID(),
        text,
    };
    todos.push(newTodo);
    createTodoElement(newTodo);
    localStorage.setItem(projectName, JSON.stringify(todos));
    todoInput.value = "";
}
function createTodoElement(todo) {
    const li = document.createElement("li");
    li.className = "todo";
    li.dataset.id = todo.id;
    const todoText = document.createElement("span");
    todoText.className = "todo-text";
    todoText.textContent = todo.text;
    li.appendChild(todoText);
    const div = document.createElement("div");
    div.className = "todo-actions";
    const todoEdit = document.createElement("button");
    todoEdit.className = "todo-edit";
    todoEdit.innerHTML = pencil;
    todoEdit.setAttribute("aria-label", "Edit Todo");
    todoEdit.setAttribute("type", "button");
    todoEdit.addEventListener("click", handleTodoEdit);
    div.appendChild(todoEdit);
    const todoDelete = document.createElement("button");
    todoDelete.className = "todo-delete";
    todoDelete.setAttribute("aria-label", "Delete Todo");
    todoDelete.setAttribute("type", "button");
    todoDelete.innerHTML = trashCan;
    todoDelete.addEventListener("click", handleTodoDelete);
    div.appendChild(todoDelete);
    li.appendChild(div);
    const todosList = document.querySelector(".todos-list");
    if (!todosList) {
        throw new Error("todos-list is undefined");
    }
    todosList.appendChild(li);
}
function handleTodoEdit(e) {
    const li = e.target?.closest("li");
    if (!li) {
        throw new Error("parent li element doesn't exist");
    }
    const textEl = li.querySelector(".todo-text");
    if (!textEl) {
        throw new Error("couldn't find the text for the todo");
    }
    const id = li.dataset.id;
    const originalText = textEl.textContent ?? "";
    li.style.display = "none";
    const input = document.createElement("input");
    input.type = "text";
    input.className = "todo-edit-input";
    input.value = originalText;
    input.setAttribute("aria-label", "Edit todo text");
    li.parentElement?.insertBefore(input, li);
    input.focus();
    input.select();
    const handleEdit = () => {
        const newText = input.value.trim();
        if (newText) {
            textEl.textContent = newText;
            const index = todos.findIndex((t) => t.id === id);
            if (index !== -1) {
                todos[index].text = newText;
                localStorage.setItem(projectName, JSON.stringify(todos));
            }
        }
        cleanup();
    };
    const keydownHandler = (ev) => {
        if (ev.key === "Enter") {
            handleEdit();
        }
        else if (ev.key === "Escape") {
            cleanup();
        }
    };
    const blurHandler = () => {
        handleEdit();
    };
    function cleanup() {
        input.removeEventListener("keydown", keydownHandler);
        input.removeEventListener("blur", blurHandler);
        input.remove();
        if (li) {
            li.style.display = "";
        }
    }
    input.addEventListener("keydown", keydownHandler);
    input.addEventListener("blur", blurHandler);
}
function handleTodoDelete(e) {
    const li = e.target?.closest("li");
    if (!li) {
        throw new Error("parent li element doesn't exist");
    }
    const id = li.dataset.id;
    const index = todos.findIndex((t) => t.id === id);
    if (index === -1) {
        throw new Error("element not found. invalid id for the todo");
    }
    todos.splice(index, 1);
    localStorage.setItem(projectName, JSON.stringify(todos));
    li.remove();
}
export {};
//# sourceMappingURL=index.js.map