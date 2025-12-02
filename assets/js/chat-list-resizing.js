class ChatListResizing {
    static OnResizerMouseDown() {
        /* Get the chat list DOM object */
        const chat_list_obj = document.getElementById('chat-list');

        /* Function to update the chat list width */
        const update_width = (event) => {
            let new_width = event.clientX;
            if (new_width > 250)
                chat_list_obj.style.width = `${new_width}px`;
            else
                chat_list_obj.style.width = `0px`;
        }

        /* Function to remove the mousemove document event listener */
        const remove_listener = (event) => {
            document.removeEventListener('mousemove', update_width)
            document.removeEventListener('mouseup', remove_listener)
        }

        /* Add event listeners */
        document.addEventListener('mousemove', update_width);
        document.addEventListener('mouseup', remove_listener);
    }
}