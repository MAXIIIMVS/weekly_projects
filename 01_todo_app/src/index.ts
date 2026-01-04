const projectName = "weekly-project-todo-app";
const trashCan = "&#128465;";
const pencil = "&#9998;";

type Todo = {
  id: ReturnType<typeof crypto.randomUUID>;
  text: string;
};

const todos: Todo[] = [];

const storedText = localStorage.getItem(projectName);
if (storedText) {
  const storedTodos = JSON.parse(storedText) as Todo[];
  storedTodos.forEach((todo) => {
    todos.push(todo);
    createTodoElement(todo);
  });
}

const todoForm = document.querySelector<HTMLFormElement>(".todo-form");

if (!todoForm) {
  throw new Error("todo-form is not defined");
}

todoForm.addEventListener("submit", submitTodo);

function submitTodo(e: SubmitEvent) {
  e.preventDefault();
  const todoInput = todoForm?.querySelector<HTMLInputElement>(".todo-input");
  if (!todoInput) {
    throw new Error("todo-input is not defined");
  }
  if (!todoInput.value) {
    return;
  }
  const newTodo: Todo = {
    id: crypto.randomUUID(),
    text: todoInput.value,
  };
  todos.push(newTodo);
  createTodoElement(newTodo);
  localStorage.setItem(projectName, JSON.stringify(todos));
  todoInput.value = "";
}

function createTodoElement(todo: Todo) {
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
  todoEdit.addEventListener("click", handleTodoEdit);
  div.appendChild(todoEdit);

  const todoDelete = document.createElement("button");
  todoDelete.className = "todo-delete";
  todoDelete.setAttribute("aria-label", "Delete Todo");
  todoDelete.innerHTML = trashCan;
  todoDelete.addEventListener("click", handleTodoDelete);
  div.appendChild(todoDelete);

  li.appendChild(div);

  const todosList = document.querySelector<HTMLUListElement>(".todos-list");
  if (!todosList) {
    throw new Error("todos-list is undefined");
  }
  todosList.appendChild(li);
}

function handleTodoEdit(e: MouseEvent) {
  const li = (e.target as HTMLElement)?.closest("li");
  if (!li) {
    throw new Error("parent li element doesn't exist");
  }

  const textEl = li.querySelector<HTMLSpanElement>(".todo-text");
  if (!textEl) {
    throw new Error("couldn't find the text for the todo");
  }

  li.style.display = "none";
  const id = li.dataset.id;

  const input = document.createElement("input");
  input.type = "text";
  input.className = "todo-edit";
  input.value = textEl.textContent ?? "";

  li.parentElement?.insertBefore(input, li);
  input.focus();
  input.select();

  const keydownHandler = (ev: KeyboardEvent) => {
    if (ev.key === "Enter") {
      const index = todos.findIndex((t) => t.id === id);
      if (index === -1) {
        throw new Error("could not find the todo");
      }
      if (input.value) {
        textEl.textContent = input.value;
        todos[index]!.text = input.value;
        localStorage.setItem(projectName, JSON.stringify(todos));
      }
      cleanup();
    } else if (ev.key === "Escape") {
      input.blur();
    }
  };

  const blurHandler = () => {
    cleanup();
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

function handleTodoDelete(e: PointerEvent) {
  const li = (e.target as HTMLElement).parentElement?.parentElement;
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
