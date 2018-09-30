import os
from tkinter import (
    Frame,
    Tk,
    PhotoImage,
    filedialog,
)
from tkinter.ttk import (
    Button,
    Entry,
    Label,
    Labelframe,
    Combobox,
)

from PIL import ImageTk, Image

from common import DEFAULT_SPRITESHEET_PATH
from tkinterapp import Application
import spritesheet
from color import rgb_to_hex, hex_to_rgb


class App(Application):
    """ Spritesheet tool GUI """

    def __init__(self, master):
        super().__init__(master)

        self.init_ui()
        self.center_window()

    def init_ui(self):
        """ Initialize GUI layout and widgets """
        self.master.title("Spritesheet Tool")
        self.padding = '1m'
        self.assetpath = os.path.join(os.getcwd(), 'assets')
        self.copyImage = PhotoImage(file=os.path.join(self.assetpath, 'copy.png'))  # 16x16 pixels
        self.colorPickerImage = PhotoImage(file=os.path.join(self.assetpath, 'colorpicker.png'))
        self.openImage = PhotoImage(file=os.path.join(self.assetpath, 'open.png'))

        self.master.grid_rowconfigure(0, weight=1)
        self.master.grid_columnconfigure(0, weight=1)

        self.previewFrame = Frame(self.master)
        self.infoFrame = Frame(self.master)

        self.settingFrame = Labelframe(self.infoFrame, text='Settings')
        self.bboxFrame = Labelframe(self.infoFrame, text='Bounding Box')
        self.spriteFrame = Labelframe(self.infoFrame, text='Sprite Preview')

        self.previewFrame.grid(column=0, row=0, sticky='nsew')
        self.infoFrame.grid(column=1, row=0, sticky='n')

        self.settingFrame.grid(column=0, columnspan=2, row=0, padx=self.padding, pady=self.padding, sticky='ew')
        self.settingFrame.grid_columnconfigure(1, weight=1)

        self.bboxFrame.grid(column=0, row=1, padx=self.padding, pady=self.padding, sticky='ew')
        self.bboxFrame.grid_columnconfigure(1, weight=1)

        self.spriteFrame.grid(column=1, row=1, padx=self.padding, pady=self.padding, sticky='nsw')
        self.spriteFrame.grid_columnconfigure(0, weight=1)
        self.spriteFrame.grid_columnconfigure(2, weight=1)
        self.spriteFrame.grid_rowconfigure(0, weight=1)
        self.spriteFrame.grid_rowconfigure(2, weight=1)

        self.spritesheetPanel = Label(self.previewFrame)
        self.spritesheetPanel.bind('<Button 1>', self.on_click_image)

        self.spritesheetPathLabel = Label(self.settingFrame, text='Spritesheet Folder')
        self.spritesheetPathButton = Button(self.settingFrame, image=self.openImage,
                                            command=self.on_change_spritesheet_path)
        self.spritesheetPathEntry = Entry(self.settingFrame, state='readonly')

        self.spritesheetLabel = Label(self.settingFrame, text='Spritesheet')
        self.spritesheetCombobox = Combobox(self.settingFrame, state='readonly')
        self.spritesheetCombobox.bind('<<ComboboxSelected>>', self.on_select_spritesheet)

        self.transColorLabel = Label(self.settingFrame, text='Transparent Color')
        self.transColorEntry = Entry(self.settingFrame, width=10, state='readonly')
        self.transColorPanel = Label(self.settingFrame)
        self.pickColorButton = Button(self.settingFrame, image=self.colorPickerImage, command=self.on_pick_bgcolor)

        validate_cmd = (self.master.register(self.validate_number_value), '%S')  # %S - char inserted
        self.borderThicknessLabel = Label(self.settingFrame, text='Border Thickness')
        self.borderThicknessEntry = Entry(self.settingFrame, validate='key', validatecommand=validate_cmd)

        self.topLabel = Label(self.bboxFrame, text='top')
        self.bottomLabel = Label(self.bboxFrame, text='bottom')
        self.leftLabel = Label(self.bboxFrame, text='left')
        self.rightLabel = Label(self.bboxFrame, text='right')

        self.topEntry = Entry(self.bboxFrame, state='readonly')
        self.bottomEntry = Entry(self.bboxFrame, state='readonly')
        self.leftEntry = Entry(self.bboxFrame, state='readonly')
        self.rightEntry = Entry(self.bboxFrame, state='readonly')

        self.copyTopButton = Button(self.bboxFrame, image=self.copyImage,
                                    command=lambda: self.on_click_copy_button(self.topEntry))
        self.copyBottomButton = Button(self.bboxFrame, image=self.copyImage,
                                       command=lambda: self.on_click_copy_button(self.bottomEntry))
        self.copyLeftButton = Button(self.bboxFrame, image=self.copyImage,
                                     command=lambda: self.on_click_copy_button(self.leftEntry))
        self.copyRightButton = Button(self.bboxFrame, image=self.copyImage,
                                      command=lambda: self.on_click_copy_button(self.rightEntry))

        self.spritePanel = Label(self.spriteFrame, border=2)

        self.spritesheetPanel.grid(row=0, column=0)

        self.spritesheetPathLabel.grid(row=0, column=0, sticky='e')
        self.spritesheetPathEntry.grid(row=0, column=1, columnspan=2, padx=(self.padding, 0), sticky='ew')
        self.spritesheetPathButton.grid(row=0, column=3, padx=self.padding, pady=(0, self.padding))

        self.spritesheetLabel.grid(row=1, column=0, sticky='e')
        self.spritesheetCombobox.grid(row=1, column=1, columnspan=3, padx=self.padding, pady=(0, self.padding),
                                      sticky='ew')

        self.transColorLabel.grid(row=2, column=0, sticky='e')
        self.transColorEntry.grid(row=2, column=1, sticky='ew', padx=(self.padding, 0))
        self.transColorPanel.grid(row=2, column=2)
        self.pickColorButton.grid(row=2, column=3, padx=self.padding, pady=(0, self.padding))

        self.borderThicknessLabel.grid(row=3, column=0, sticky='e')
        self.borderThicknessEntry.grid(row=3, column=1, columnspan=3, sticky='ew',
                                       padx=self.padding, pady=(0, self.padding))

        self.topLabel.grid(row=0, column=0, sticky='e', padx=self.padding, pady=self.padding)
        self.bottomLabel.grid(row=1, column=0, sticky='e', padx=self.padding, pady=self.padding)
        self.leftLabel.grid(row=2, column=0, sticky='e', padx=self.padding, pady=self.padding)
        self.rightLabel.grid(row=3, column=0, sticky='e', padx=self.padding, pady=self.padding)

        self.topEntry.grid(row=0, column=1, sticky='ew')
        self.bottomEntry.grid(row=1, column=1, sticky='ew')
        self.leftEntry.grid(row=2, column=1, sticky='ew')
        self.rightEntry.grid(row=3, column=1, sticky='ew')

        self.copyTopButton.grid(row=0, column=2, padx=self.padding)
        self.copyBottomButton.grid(row=1, column=2, padx=self.padding)
        self.copyLeftButton.grid(row=2, column=2, padx=self.padding)
        self.copyRightButton.grid(row=3, column=2, padx=self.padding)

        self.spritePanel.grid(row=1, column=1, sticky='nsew')
        self.init_value()

    def init_value(self):
        """ Initialize default values on startup """
        self.picking_color = False

        self.set_readonly_text(self.spritesheetPathEntry, DEFAULT_SPRITESHEET_PATH)
        self.update_spritesheet_list()

        self.set_spritesheet_panel()
        self.set_transparent_color(self.spritesheet_image.getpixel((0, 0)))
        self.set_text(self.borderThicknessEntry, 1)

        self.center_window()

    def update_spritesheet_list(self):
        spritesheet_path = self.spritesheetPathEntry.get()
        spritesheets = []

        for filename in os.listdir(spritesheet_path):
            if filename.endswith('.png'):
                name = os.path.splitext(filename)[0]
                spritesheets.append(name)

        self.spritesheetCombobox.configure(value=spritesheets)
        if len(spritesheets) > 0:
            self.spritesheetCombobox.current(0)
        else:
            self.spritesheetCombobox.set('')

    def set_spritesheet_panel(self):
        selected_spritesheet = self.spritesheetCombobox.get()

        if selected_spritesheet != '':
            image_path = os.path.join(self.spritesheetPathEntry.get(), selected_spritesheet + '.png')
            self.spritesheet_image = Image.open(image_path).convert('RGB')
            self.spritesheet_photo = ImageTk.PhotoImage(self.spritesheet_image)
            self.spritesheetPanel.configure(image=self.spritesheet_photo)

    def set_transparent_color(self, rgb_color):
        self.set_readonly_text(self.transColorEntry, rgb_to_hex(rgb_color))
        self.trans_color_photo = ImageTk.PhotoImage(Image.new(self.spritesheet_image.mode, (19, 19), rgb_color))
        self.transColorPanel.configure(image=self.trans_color_photo)

    def resize(self):
        width = self.spritesheet_photo.width() + self.infoFrame.winfo_width()
        height = max(self.spritesheet_photo.height(), self.infoFrame.winfo_height())

        self.master.geometry('{}x{}'.format(width, height))

    def on_change_spritesheet_path(self):
        spritesheet_path = filedialog.askdirectory()

        if spritesheet_path != '':
            self.set_readonly_text(self.spritesheetPathEntry, spritesheet_path)
            self.update_spritesheet_list()

    def on_select_spritesheet(self, e):
        self.set_spritesheet_panel()
        self.set_transparent_color(self.spritesheet_image.getpixel((0, 0)))
        self.resize()
        self.center_window()

    def on_pick_bgcolor(self):
        self.picking_color = True
        self.master.config(cursor='tcross')

    def on_click_image(self, e):
        if self.picking_color:
            self.pick_bgcolor(e)
        else:
            self.update_sprite_bbox(e)

    def pick_bgcolor(self, e):
        selected_color = self.spritesheet_image.getpixel((e.x, e.y))
        self.set_transparent_color(selected_color)
        self.picking_color = False
        self.master.config(cursor='arrow')

    def update_sprite_bbox(self, e):
        bbox = spritesheet.get_sprite_bbox(
            (e.x, e.y),
            self.spritesheet_image,
            hex_to_rgb(self.transColorEntry.get()),
            int(self.borderThicknessEntry.get()))

        if bbox is None:
            return

        left, top, right, bottom = bbox

        self.set_readonly_text(self.leftEntry, left)
        self.set_readonly_text(self.topEntry, top)
        self.set_readonly_text(self.rightEntry, right)
        self.set_readonly_text(self.bottomEntry, bottom)

        self.sprite_image = self.spritesheet_image.crop((left, top, right, bottom))
        self.sprite_photo = ImageTk.PhotoImage(self.sprite_image)
        self.spritePanel.configure(image=self.sprite_photo)

    def on_click_copy_button(self, entry):
        self.master.clipboard_clear()
        self.master.clipboard_append(entry.get())
        self.master.update()  # now it stays on the clipboard after the window is closed


def main():
    root = Tk()

    app = App(root)
    app.mainloop()


if __name__ == '__main__':
    main()