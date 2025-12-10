class ChatList {
    static Resize(width, chat_list_obj = document.getElementById('chat-list')) {
        chat_list_obj.style.width = width;
    }

    static OnResizerMouseDown() {
        /* Get the chat list DOM object */
        const chat_list_obj = document.getElementById('chat-list');

        /* Function to update the chat list width */
        const update_width = (event) => {
            let new_width = event.clientX;
            if (new_width > 250)
                this.Resize(`${new_width}px`, chat_list_obj);
            else
                this.Resize('0px', chat_list_obj);
        };

        /* Function to remove the mousemove document event listener */
        const remove_listener = () => {
            document.removeEventListener('mousemove', update_width);
            document.removeEventListener('mouseup', remove_listener);
        };

        /* Add event listeners */
        document.addEventListener('mousemove', update_width);
        document.addEventListener('mouseup', remove_listener);
    }
}