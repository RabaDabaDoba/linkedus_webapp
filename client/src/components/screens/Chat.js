import React from 'react';
import { Link } from 'react-router-dom';
import { ThemeProvider, Message, MessageText, MessageList, MessageGroup,
  TextComposer, Row, TextInput, SendButton } from '@livechat/ui-kit';
import ArrowBack from '@material-ui/icons/ArrowBackIos';
import './Chat.css';


const TEMPID = 1;


class MessagesContent extends React.Component {

  constructor(props){
    super(props)
    this.state = {
      posts: [],
      from_id: null,
      to_id: null,
      chat_id: null,
      message: null,
      sendMessage: 'This is a hardcoded message',
      messagingTo: null
    }
  }

  cardClick = (i) => {
    alert('SENDING TO DB');
      let data = {
        from_id: TEMPID,
        to_id: this.state.posts[i].to_id,
        chat_id: this.state.posts[i].chat_id,
        message: this.state.posts[i].sendMessage

      };
      console.log(data);
      fetch('/written-message', {
        method:'POST',
        body: JSON.stringify(data),
        headers: {
              "Content-Type": "application/json"
          }

      }).then((res)=>{
        if(res.ok){
          return res.json();
        }
        else{
          throw new Error ('Wrong');
        }
      })
      .then((json)=>{
        console.log(json);
      })


    }



  componentDidMount(){
    this.getMessages();
  }

  getMessages = _ => {
    fetch('/api/messages')
      .then(response => response.json())
      .then(response => this.setState({ posts:response.data }))
      .catch(err => console.error(err))
  }

  render() {

    const messages = this.state.posts.map((item, i) => (

      <div className='messenger'>
        <MessageList active>
      {(() => {
        switch (item.from_id) {
          case TEMPID:   return (<MessageGroup onlyFirstWithMeta>
            <Message date={item.createdDate.substring(11, 16)} isOwn={true}>
              <MessageText className='bubble_right'>
                {item.message}
              </MessageText>
            </Message>
          </MessageGroup>);
          default:      return(<MessageGroup
            avatar="https://media.licdn.com/dms/image/C4E03AQFdhqSSucWLTg/profile-displayphoto-shrink_800_800/0?e=1550102400&v=beta&t=dsJgTRO-OBZ1GzdaZH7cv9XKqsczC0UJV5KK_PhXtFI"
            onlyFirstWithMeta>
            <Message authorName="Weiqing Huang" date= {item.createdDate.substring(11, 16)}>
              <MessageText className='bubble_left' onClick={() => this.cardClick(i)}>
                {item.message}
              </MessageText>
            </Message>
          </MessageGroup>

        );
        }
      })()}
      </MessageList>
      <TextComposer className='textcomposer' >
        <Row align="center">
          <TextInput onChangeText= {message => this.setState({message})}/>
          <SendButton onClick={(msg) => alert(msg)} fit/>
        </Row>
      </TextComposer>
    </div>

    ));


    return (
      messages
    );
console.log(sendMessage)

  }
}

class MessagesScreen extends React.Component {
  state = {
    posts: []
  }

  componentDidMount(){
    this.getNameChat();
  }

  getNameChat = _ => {
    fetch('/api/name-chat')
      .then(response => response.json())
      .then(response => this.setState({ posts:response.data }))
      .catch(err => console.error(err))
  }


  render() {
    const messageTop = this.state.posts.map((item, i) => (
      <div className='phone'>
        <div className='phone__header'>
          <Link to='/messages' style={{ color:'white' }}><span><ArrowBack /></span></Link>
          {/* <span>Michale Smith</span> */}
          <span>{item.name}</span>
          <a href="https://www.linkedin.com/in/wqhuang-ustc/"
            rel="noopener noreferrer"
            style={{ color:'white'}}
            ><span className='fab fa-linkedin' /></a>
        </div>

        <div className='phone-content__wrapper'>
        <ThemeProvider>

                <MessagesContent />

          </ThemeProvider>
        </div>


      </div>




    ));
    return (messageTop);
  }
}

export default MessagesScreen;
