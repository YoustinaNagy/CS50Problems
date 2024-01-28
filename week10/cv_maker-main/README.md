# cv_maker
CV Maker using Flask - HTML - CSS - JS - BootStrap

#### Video Demo: https://www.youtube.com/watch?v=KlHQVQspY5M

#### Description:
The project consists of multiple forms and a layout for the generated CV.
- The forms should be found under `/templates` include:
   - Personal Info(current): contains personal information, such as name, address, social media profiles, and a personal photo.
   - Experience: It is a dynamic form, allowing you to add detailed work experiences. (Currently deleting experiences is not supported)
   - Learing & Certifications: It is a dynamic form, allowing you to add certifications. (Currently deleting certificates is not supported)
   - Skills: dynamic form to add/updates your skills for the level of profeciency.
   - Languages: dynamic form to add/updates your languages for the level of fluency.
   - References: any additional references to add
- The CV is genetated automatically based on the user recorded responses to the forms.
- Some forms are associated with static assets, such as JavaScript files, images, icons, and sylesheets.
   - For example, Experience form is located under `/templates/experiences.html`. It is associated with the JavaScript file in `/static/js/loadMoreExperiences.js`.
- This project utilizes the built in support for template rendering using Jinja. For example, all html files extend a base template with the name `template_navbar.html`.
- There are more static assets found under `/static` that includes:
   - `css/`: all CSS files related to the project, including minified versions of bootstrap css.
   - `icon-font`: all fonts and icons for the project.
   - `img`: used static images referenced in some project's templates.
   - `js`: JavaScript files for the project.
- The main Python handler for the project is named as `app.py`. It contains the following
   - Configurations to store sessions on the file system.
   - Initializing the connection with the database.
   - Endpoints for the application, including all `GET` and `POST` handlers.
   - Validations and verifications for submitted information via forms.
- The helper functions, such as `login_required` decorators should be found in `helpers.py`.
- For the database information, you can check `cv_maker.db`.
- For the license, you can check `LICENSE`.
- Requirements and versions should be located in `requirements.txt`

#### Future plans.
- Supporting deleting individual sections from forms.
- Adding a logout button instead of logging out through the URL `/logout`.
- optimizing query performance.

##### How to use
1. Register using your username and password.
2. Fill up your info in the following sections
   - Personal Info(current)
   - Experience
   - Learing & Certifications
   - Skills
   - Languages
   - References
3. Click on the logo on the top-left corner and check your CV.

##### How to contribute
1. Clone the repository.
2. Install the dependencies using `pip install -r requirements.txt`
3. Run the application using `flask run --host=0.0.0.0`

